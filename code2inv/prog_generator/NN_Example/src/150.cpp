// https://github.com/pytorch/examples/blob/master/cpp/mnist/mnist.cpp
// Sum over prediction of "n" handwritten digits. from 0's set to 9's set.

#include <150.h>
#include <assert.h>
#include <inttypes.h>
#include <libhfuzz/libhfuzz.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <torch/script.h>
#include <torch/torch.h>
#include <string.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag) \
    if (!cond) flag = 1;

#define assume(cond) \
    if (!cond) continue;

#define INV(sum, n, i, index) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE* fptr, char* buff, long long int sum, long long int n, long long int i,
              long long int index) {
    int f = preflag;
    aflcrash(INV(sum, n, i, index), preflag);
    if (f == 0 && preflag == 1) {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "sum", sum, "n", n, "i",
                i, "index", index);
        assert(0);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE* fptr, char* buff, long long int temp_sum, long long int temp_n,
               long long int temp_i, long long int temp_index, long long int sum, long long int n,
               long long int i, long long int index) {
    int f = loopflag;
    aflcrash(INV(sum, n, i, index), loopflag);
    if (f == 0 && loopflag == 1) {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "sum", temp_sum,
                "n", temp_n, "i", temp_i, "index", temp_index);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "sum", sum, "n", n,
                "i", i, "index", index);
        assert(0);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, sum, n, i, index)                                             \
                                                                                                  \
    {                                                                                             \
        int f = postflag;                                                                         \
                                                                                                  \
        aflcrash(cond, postflag);                                                                 \
                                                                                                  \
        if (f == 0 && postflag == 1) {                                                            \
            fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "sum", sum, "n", \
                    n, "i", i, "index", index);                                                   \
            assert(0);                                                                            \
        }                                                                                         \
    }

FILE* fptr;

/**
 * @brief Source Images
 * When running dryRun.sh from RQ3 Folder directly,
 * the paths are
 *    ./data/MNIST/raw
 *    ./mnist_model_cpp.pt
 */

#ifdef INPLACE  // When running the file from RQ3 Folder directly,
#undef OUTPLACE
const char* kDataRoot = "./data/MNIST/raw";
const char* modelPTFile = "./mnist_model_cpp.pt";
#endif

#ifdef OUTPLACE  // With the learner.
#undef INPLACE
const char* kDataRoot = "NN_Example/data/MNIST/raw";
const char* modelPTFile = "NN_Example/mnist_model_cpp.pt";
#endif

// The batch size for training.
// This is not needed since we
// use a trained model.
const int64_t kTrainBatchSize = 64;

// The batch size for testing.
const int64_t kTestBatchSize = 1;

auto test_dataset =
    torch::data::datasets::MNIST(kDataRoot, torch::data::datasets::MNIST::Mode::kTest)
        .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
        .map(torch::data::transforms::Stack<>());

const size_t dataset_size = test_dataset.size().value();

auto data_loader = torch::data::make_data_loader(std::move(test_dataset), kTestBatchSize);

torch::data::Example<> get_image_data(int image_index) {
    // auto data_loader =
    //     torch::data::make_data_loader(std::move(test_dataset), kTestBatchSize);
    for (torch::data::Example<>& batch : *(data_loader)) {
        auto data = batch.data;
        auto targets = batch.target;
        int32_t target_number = (batch.target).template item<int64_t>();
        if (target_number == (image_index / 10)) {
            return batch;
        }
    }
}

int32_t predict(torch::data::Example<> image) {
    // Deserialize the ScriptModule from a file using torch::jit::load().
    // ./mnist_example ../<model.pt>
    torch::jit::Module module = torch::jit::load(modelPTFile);

    torch::NoGradGuard no_grad;
    module.eval();

    double test_loss = 0;
    int32_t correct = 0, total = 0, pred_number = 0, target_number = 0;

    auto data = image.data;
    auto targets = image.target;

    target_number = (targets).template item<int64_t>();

    std::vector<torch::jit::IValue> mnist_input;
    std::vector<torch::jit::IValue> mnist_labelled_output;

    mnist_input.push_back(data);

    auto output = module.forward(mnist_input).toTensor();

    test_loss += torch::nll_loss(output, targets,
                                 /*weight=*/{}, torch::Reduction::Sum)
                     .template item<float>();

    auto pred = output.argmax(1);
    pred_number = pred.template item<int64_t>();

    std::fprintf(fptr, "Prediction : %d | Target : %d\n", pred_number, target_number);

    // Can be a mis-prediction +9/-9 off round error.
    return pred_number;
}

// int arr[100] = {9,  5,  8,  0,  3,  4,  7,  6,  1,  2,  12, 15, 18, 19, 16,
//                 10, 11, 14, 17, 13, 23, 20, 26, 21, 22, 29, 27, 28, 24, 25,
//                 36, 34, 32, 30, 33, 35, 39, 37, 31, 38, 41, 48, 45, 43, 46,
//                 42, 44, 47, 49, 40, 59, 55, 54, 50, 52, 53, 58, 51, 57, 56,
//                 69, 60, 64, 63, 68, 65, 61, 67, 62, 66, 75, 70, 79, 73, 71,
//                 74, 72, 76, 78, 77, 85, 84, 87, 89, 80, 81, 86, 82, 88, 83,
//                 96, 90, 95, 91, 98, 93, 94, 92, 99, 97};

int main(int argc, const char* argv[]) {
    // We consider 100 digits data set to sum over.
    // for any index i : i <= n and represents
    // the image of i / 10.

    // Eg : i = 90; it represents image "9" from dataset.
    long long int n = 100;

    // Populate digit_data with iamge data.
    std::vector<torch::data::Example<>> digit_data(n);
    for (int i = 0; i < n; i++) {
        digit_data[i] = get_image_data(i);
    }

    // variable declarations
    long long int sum;
    long long int i;
    long long int index;

    char buff[2048];
    memset(buff, '\0', sizeof(buff));

    fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 2048);

    for (;;) {
        size_t len;
        const uint8_t* buf;

        HF_ITER(&buf, &len);
        counter++;

        int choices = buf[5];

        sum = buf[7];
        index = buf[9];
        i = buf[6];

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n", "sum", sum, "n", n, "i",
                 i, "index", index);

        if (choices > 100) {
            // pre-conditions
            assume((preflag == 0));
            sum = 0;
            index = 0;
            i = 0;
            precount++;
            // fprintf(fptr, "Pre\n");
            precheck(fptr, vars, sum, n, i, index);
        } else {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(sum, n, i, index));

            // Loop Condition
            if (index < n) {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((index < n) && k--) {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_sum = sum;
                    long long int temp_n = n;
                    long long int temp_i = i;
                    long long int temp_index = index;

                    // torch::data::Example<> data = get_image_data(i);
                    sum += predict(digit_data[index]);
                    index += 1;
                    // fprintf(fptr, "Loop\n");

                    loopcount++;
                    loopcheck(fptr, vars, temp_sum, temp_n, temp_i, temp_index, sum, n, i, index);
                }
            } else {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                if (index == n) {
                    // fprintf(fptr, "Post\n");
                    postcheck(fptr, vars, ((sum >= 441) && (sum <= 459)), sum, n, i, index)
                }
            }
        }

        if (preflag + loopflag + postflag == 0 && counter == 50) {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n", "precount", precount, "loopcount",
                    loopcount, "postcount", postcount);
            counter = 0;
        }

        if (preflag + loopflag + postflag >= 3) {
            fclose(fptr);
            assert(0);
        }
    }

    fclose(fptr);
    return 0;
}

// (correct - 9 <= actual_sum <= correct + 9 )