# Getting Started

We describe in details the steps required to install and run Achar tool. Achar tool requires the following operating system and system requirements. It takes around 15 mins to run all the commands here and getting the tool (Achar) up and running. This may vary depending on the specific system load and internet connection speed (involved in downloading the required packages).

- **OS** : Ubuntu 20.04 or higher. (We have not extensively tested on Ubuntu 18.04 but it must be supported.)
- **RAM** : 16GB or higher is recommended.
- **CPU** (cores) : Intel 64-bit/32-bit CPU with 4 or more logical cores. (Intel i5 7th Gen or higher.)
- **HDDs/SSDs** (secondary memory) : We recommend atleast 30GB of free space for all the experimental evaluation to be conducted.
- **Internet Access** : We require a working internet connection to download and install the dependencies for our tool. 
- **Docker** : We recommend using `focal` as the Ubuntu flavor incase using a fresh docker for the artifact evaluation. See [docker resources](#running-docker) we used as recommended setting for running a docker image.

## Tool Installation

Extract the artifact zip and keep in the any directory of choice in your local machine. We provide a script `install.sh` to run all the steps neccessary to setup the Achar tool (requires `sudo` access to install packages). Please make sure there is internet access to download the required dependencies. Incase of any issues in the script, we recommend following the steps in [Manual Installation](#manual-installation) section or try out our [docker image](#docker-image-achar-tool) which has all the codebase and dependencies installed. **\$HOME dir is same as the default ~ dir.**

- Note : This script can't be run directly on a docker image, it is for installation on a regular machine running OS as mentioned earlier. We recommend following the steps in [Manual Installation](#manual-installation) section if running on a fresh image of a docker.

```bash
# From the directory where the artifact is extracted.
$ ./install.sh
```

## Run a single example.

Running the `Achar` tool is easy now. To run any benchmark example use the `runbench.sh` script. 
Here we show the command to run for one (`example 11`) of the 133 benchmark example using the `fuzzer` backend.
The tool (`Achar`) is built on [Code2Inv](https://github.com/PL-ML/code2inv).

```bash
$ ./runbench.sh 11 fuzz_spec
```

### Expected Logs from running Tool (`Achar`).

We show the expected output from the tool on running `example 11` using the above command. The tool first does initialization and creates 
the `pytorch` neural network layers using the program's SSA form and the grammar given. The line after `Solving...` to `MAX CHILD .. ` shows
the grammar used for the example. Some of the lines have been ommitted for brevity. The output logs for all other examples and modes 
are quite the same except for the fact that the `fuzzer` type changes and the `candidate` invariants differ from example to example in each log.

```bash
K-Induction : 64, 64
OP_FILE results/inv_result_11_fuzz_spec.log
 ==== Solving timeout=10s, epoch=8, K=64 | File : 11 ==== 
{'S': [['S1'], ['S2']], 'S1': [['(', 'C1', ')'], ['(', 'C1', '||', 'C1', ')'], ['(', 'C1', '||', 
	'C1', '||', 'C1', ')']], 'C1': [['p'], ['(', 'p', '&&', 'p', ')']], 
'S2': [['(', 'C2', ')'], ['(', 'C2', '&&', 'C2', ')'], ['(', 'C2', '&&', 'C2', '&&', 'C2',')']], 
	'C2': [['p'], ['(', 'p', '||', 'p', ')']], 'p': [['var', 'cmp', 
'expr']], 'expr': [['(', 'var', 'op', 'var', ')'], ['(', 'var', 'op', 'const', ')'], 
	['(', 'const', 'op', 'var', ')'], ['(', 'const', 'op', 'const', ')'], ['var'], 
['const']], 'cmp': [['<'], ['>'], ['=='], ['<='], ['>=']], 'op': [['+'], ['-'], ['*']]}
MAX CHILD 7
VAR FORMAT ssa
====== begin of s2v configuration ======
| msg_average = 0
======   end of s2v configuration ======
a Linear inited
a GRUCell inited
a Linear inited
a Linear inited
a Linear inited
a Parameter inited
a Parameter inited
...
...
...
a Linear inited
a Linear inited
a Parameter inited
a Parameter inited
a Parameter inited
  0%|          | 0/100 [00:00<?, ?it/s]
  	UserWarning: nn.functional.sigmoid is deprecated. Use torch.sigmoid instead.
  warnings.warn("nn.functional.sigmoid is deprecated. Use torch.sigmoid instead.")
/usr/local/lib/python3.8/dist-packages/torch/nn/functional.py:1933: 
	UserWarning: nn.functional.tanh is deprecated. Use torch.tanh instead.
  warnings.warn("nn.functional.tanh is deprecated. Use torch.tanh instead.")
2022-05-25 14:07:31.126344 [Fuzz Checker] ( y > ( y * x ) && ( x < ( 0 + x ) || y >= (y+10)))
2022-05-25 14:07:34.099743 [Fuzz Checker] ( y <= ( y - y ) || x >= ( 20 * x ) )
2022-05-25 14:07:35.435776 [Fuzz Checker] ( x > ( y * x ) || x <= ( x + y ) )
2022-05-25 14:07:36.750273 [Fuzz Checker] ( x == x )
2022-05-25 14:07:38.116565 [Fuzz Checker] ( y > ( y - x ) && ( x == 0 || x == 10 ) && x>=(20-x))
2022-05-25 14:07:39.456399 [Fuzz Checker] ( ( x == ( 0 * y ) && x >= 10 ) )
2022-05-25 14:07:41.216518 [Fuzz Checker] 
	( ( x >= x || x <= 10 ) && ( x >= ( x * 20 ) || x == 0 ) && ( y >= ( y - 20 ) || x>=(x+y)))
2022-05-25 14:07:43.111953 [Fuzz Checker] 
	( ( y > ( y - x ) && y > ( x - y ) ) || ( x < ( 20 + y ) && y <= ( y - x ) ) )
2022-05-25 14:07:44.892188 [Fuzz Checker] 
	( ( x <= ( 0 + 10 ) || y >= ( x - 10 ) ) && ( x > ( y - 20 ) || x <= 20 ) )
2022-05-25 14:07:47.739473 [Fuzz Checker] 
	( ( y <= ( 10 + y ) || y == 0 ) && ( x < ( 10 - y ) || x <= ( x - 20 ) ) )
...
...
2022-05-25 14:07:58.641014 [Fuzz Checker] ( ( x < ( x + y ) || x < 20 ) )     
2022-05-25 14:08:02.145581 [Fuzz Checker] ( ( x < ( 10 + y ) || x > ( 20 + x ) ) )
2022-05-25 14:08:21.777981 [Fuzz Checker] ( ( x <= ( 10 + y ) && y < ( 20 + y ) ) )
found a solution for 0 , sol: ( ( x <= ( 10 + y ) && y < ( 20 + y ) ) )       
z3_report time: 61.11 pid: 0 stats: Counter({'ce-I:': 4281, 'ce-T:': 2166, 
	'ce-F:': 1217, 'boogie_result': 612, 'actual_z3': 15})
Writing logs to results/inv_result_11_fuzz_spec.log                           
avg reward so far : -0.55838:  61%|██████    | 61/100 [01:01<00:39,  1.00s/it]

real	1m1.802s
user	2m34.920s
sys	0m8.819s

	K-Induction : 64, 64
	Invariant Checked : ( ( x <= ( 10 + y ) && y < ( 20 + y ) ) )
	CounterExample : [None, None, None]
	Simplifed Expression : [x <= 10 + y]
```

- The lines containing the `[Fuzz Checker]` are the logs from the fuzzer, it shows the invariant expressions from the learner, that the 
fuzzer backend (reachability oracle from the main paper) was able to reject to successful since these invariants are wrong invariants.

- Finally the line `found a solution for 0 ...` is printed which corresponds to the invariant for which the fuzzer backend was not able to
generate any counterexample, and this passed off as a *likely* almost correct invariant for the `example 11`. 

- Once *Achar* converges to this result, the correctness of the invariant is checked with `Z3` tool over the `SMT` encoding of the program.
This corresponds to `Invariant Checked : ...` line. Since the converged invariant is correct for the given program, `Z3` produces no 
counterexample instilling confidence that the `converged` invariant is actually correct.

- It took a total of `61.11 sec` to run the tool on the example and report back the `converged` invariant, shown on line `z3_report time: ...`.
 
- It took, `15` counterexamples from the `fuzzer` backend to finally `converge` to an invariant shown by `'actual_z3': 15` with the `K-bound` factor 
of 64. (Refer to sections 3 and 5 in our main paper).

- General Command.

```bash
$ ./runbench.sh <example_number> <tool_mode>
```

- Use `-h` flag with the script to get the help. 
It specifies the `modes` and `benchmark` examples available for `Achar` to run

```bash
$ ./runbench.sh -h
```

- Hybrid `mod2check()` example on Achar tool. 

```bash
$  ./runbench.sh 2 fuzz_hybrid
```

### Interesting Examples

- Running the `CNN` Example in section 5.1.2 from the main paper `(Verifying programs invoking CNN)`. 

```bash
$ ./runbench.sh 150 fuzz_nn
```

- Open-Program Benchmark Example 2 : isprime() // Paper Example [isprime()]

```bash
$ ./runbench.sh 2 fuzz_open
```

- Open-Program Benchmark Example 1 : sum() // Sum of squares

```bash
$ ./runbench.sh 1 fuzz_open
```

- Open-Program Benchmark Example 8 : multiply() // Multiply Example

```bash
$ ./runbench.sh 8 fuzz_open
```


## Docker Image (Achar Tool)

Incase of any issues faced regarding environment setup or errors in running `Achar` tool, we strongly suggest you to use our docker image available at [acharver1/achar](https://hub.docker.com/r/acharver1/achar) which has all the scripts, codebase and the environment readily available for evaluation. (See section [Running Docker](#running-docker))

- Docker Image Link : [acharver1/achar](https://hub.docker.com/r/acharver1/achar)

```bash
$ docker pull acharver1/achar:latest
$ docker run --name achar --cpus=4 --memory=16g -it acharver1/achar:latest
```

# Detailed Description.

In this section we present the process to run the experiments listed out in **Section-5** of our paper. Incase of any issues faced regarding environment setup or errors in running the experiment, we strongly suggest you to use our docker image available as [acharver1/achar](https://hub.docker.com/r/acharver1/achar) which has all the scripts, codebase and the environment readily available for evaluation (See section [Running Docker](#running-docker)). We also provide `Complete_Results.pdf` (over all 15 open programs and 133 Benchmark programs based on experimental results shown in the paper.) and `Achar-Paper.pdf`, the PDF of the main paper for quick reference as a part of the artifact tar zip. 

The main scripts for running all the benchmark examples (133) is present in the `scripts` folder relative to the parent directory of the tool (`code2inv/scripts` folder)

## How to run the experiments?

The following bash scripts will run the experiments required to generate the data for **all of RQ1, RQ2, RQ3 and RQ4 sections of the main paper**. We also mention the folders and the final generated CSV files and logs that substantiate the results we show in the paper. A general description of the scripts follow. These scripts are long running scripts, each of which take approximately `14 hours` to run on all 133 examples, some take even more. **As our learner is randomized, for both the baseline (`Code2Inv`) tool and for `Achar`, we run the benchmarks 3 times and collect the best performance.It requires running the scripts three times in succession.** 

- `benchmark_all_z3.sh` -- This script runs `Code2Inv` tool on all 133 benchmark examples. This is a long running script, it takes `21 hours` to run on all 133 examples. We recommend to use `nohup &` with `disown` to keep the script running in the background.

- `benchmark_fuzz_all_spec.sh` -- This script runs `Achar` tool on all 133 benchmark examples under the setting that the teacher returns all the 3 counterexample models. Takes three arguments `timeout`, `epoch` and `k-bounded` factor. Use it as follows `./benchmark_fuzz_all_spec.sh 10 8 64`. This is a long running script, it takes `22 hours` to run on all 133 examples. We recommend to use `nohup &` with `disown` to keep the script running in the background.

- `benchmark_fuzz_spec.sh` -- This script runs `Achar` tool on all 133 benchmark examples under the setting that the teacher returns the first counterexample. Takes three arguments `timeout`, `epoch` and `k-bounded` factor. Use it as follows 
`./benchmark_fuzz_spec.sh 10 8 64`. This is a long running script, it takes `14 hours` to run on all 133 examples. We recommend to use `nohup &` with `disown` to keep the script running in the background.

- `benchmark_hybrid_loop_spec.sh` -- This script runs `Achar` tool on all 133 benchmark examples under the hybrid setting where the statements in the `loopbody` (loop body) contain an `opaque` operation and the teacher returns the first counterexample. Takes three arguments `timeout`, `epoch` and `k-bounded` factor. Use it as follows `./benchmark_hybrid_loop_spec.sh 10 8 64`. This is a long running script, it takes `14 hours` to run on all 133 examples. We recommend to use `nohup &` with `disown` to keep the script running in the background.

- `benchmark_hybrid_pre_spec.sh` -- -- This script runs `Achar` tool on all 133 benchmark examples under the hybrid setting where the statements in the `prebody` (loop header) contain an `opaque` operation and the teacher returns the first counterexample. Takes three arguments `timeout`, `epoch` and `k-bounded` factor. Use it as follows `./benchmark_hybrid_pre_spec.sh 10 8 64`. This is a long running script, it takes `14 hours` to run on all 133 examples. We recommend to use `nohup &` with `disown` to keep the script running in the background.

- `benchmark_single_z3.sh` -- This script runs `Code2Inv` tool on all 133 benchmark examples under setting that the Z3 returns the first counterexample instead of all the three counterexamples.  Takes three arguments `timeout`, `epoch` and `k-bounded` factor. Use it as follows `./benchmark_single_z3.sh 10 8 64`. This is a long running script, it takes `14 hours` to run on all 133 examples. We recommend to use `nohup &` with `disown` to keep the script running in the background.

- `getSolved_all.sh` & `getSolved.sh` -- These scripts are called internally by the above scripts once the tool run on all 133 examples are complete. These scripts generate the CSV which summarizes the statistics of the whole run.

An example use of the nohup command to run a long running script.

```bash
# nohup and & to run command in the background over an SSH connection. 
# nohup may not be required if running on own local machine. disown to prevent process hang after exit.
$ nohup ./benchmark_fuzz_spec.sh 10 8 64 > achar.log 2> achar_err.log < /dev/null & disown
```

## (RQ1) Synthesis Effectiveness [Section 5.1 from the main paper]

- `Achar-baseline` VS `Code2Inv`. (Time and Counterexamples(Cex) results)

Run the following scripts to run the tools on all 133 examples and finally generate the CSVs data from the run.

```bash
# Run Achar tool on all 133 examples, 10sec timeout, 8 Epochs, K=64.
$ ./benchmark_fuzz_spec.sh 10 8 64

# Run Code2Inv tool on all 133 examples, 10sec timeout, 8 Epochs
$ ./benchmark_all_z3.sh 10 8 64
```

## (RQ2) Runtime cost [Section 5.2 from the main paper]

- Timeout 10s vs 20s for `Achar` Tool

Run the following scripts to run `Achar` tool on all 133 examples and finally generate the CSVs data from the run.

```bash
# Run Achar tool on all 133 examples, 10sec timeout, 8 Epochs, K=64.
$ ./benchmark_fuzz_spec.sh 10 8 64

# Run Code2Inv tool on all 133 examples, 20sec timeout, 8 Epochs, K=64.
$ ./benchmark_fuzz_spec.sh 20 8 64
```

## (RQ3) Hybrid strategy [Section 5.3 from the main paper]

- `Achar Hybrid` (pre) vs `Achar Hybrid` (loop)  vs `Achar-Baseline`
- `Achar Hybrid` mode summary data

Run the following scripts to run `Achar` tool on all 133 examples and finally generate the CSVs data from the run.

```bash
# Run Achar tool on all 133 examples, 10sec timeout, 8 Epochs, K=64
# with `pre` containing opaque operations.
$ ./benchmark_hybrid_pre_spec.sh 10 8 64

# Run Code2Inv tool on all 133 examples, 20sec timeout, 8 Epochs, K=64.
# with `loop` containing opaque operations.
$ ./benchmark_hybrid_loop_spec.sh 20 8 64
```

## (RQ4) Optimizations and hyperparameters [Section 5.4 from the main paper]

- `Achar (all)` vs `Achar (Single)` model. 

```bash
# Run Achar tool on all 133 examples, 10sec timeout, 8 Epochs, K=64.
# Teacher returning all 3 counterexamples instead of the first counterexample.
$ ./benchmark_fuzz_all_spec.sh 10 8 64
```

- K-bounded hyperparameter.

`Achar` tool run on all 133 examples with different values of `K-bounded` parameters. 
We run Achar for the following values of `K` (K=1,K=2,K=16,k=32,K=64,K=128) with a timeout 
of `10sec` and for `8 epochs` for all the runs.

```bash
# K=1
$ ./benchmark_fuzz_spec.sh 10 8 1
# K=2
$ ./benchmark_fuzz_spec.sh 10 8 2
# K=16
$ ./benchmark_fuzz_spec.sh 10 8 16
# K=32
$ ./benchmark_fuzz_spec.sh 10 8 32
# K=128
$ ./benchmark_fuzz_spec.sh 10 8 128
```

## Running Open Benchmark Programs [Section 5.1.2 from the main paper]

The time(secs) and the number of counterexamples generated is reported(shown on the `terminal`) after 
`Achar` tool run on the examples. There are  `15 examples` in total. Each example should take less than `15 mins` 
to run and produce the invariant (timing may change subject to actual machine configuration and docker resources (if run on docker)).

```bash
$ ./runbench.sh 1 fuzz_open
$ ./runbench.sh 2 fuzz_open
$ ./runbench.sh 3 fuzz_open
$ ./runbench.sh 4 fuzz_open
$ ./runbench.sh 5 fuzz_open
$ ./runbench.sh 6 fuzz_open
$ ./runbench.sh 7 fuzz_open
$ ./runbench.sh 8 fuzz_open
$ ./runbench.sh 9 fuzz_open
$ ./runbench.sh 10 fuzz_open
$ ./runbench.sh 11 fuzz_open
$ ./runbench.sh 12 fuzz_open
$ ./runbench.sh 14 fuzz_open
$ ./runbench.sh 15 fuzz_open
```

- Running the `CNN` Example in section 5.1.2 from the main paper `(Verifying programs invoking CNN)`. 

```bash
$ ./runbench.sh 150 fuzz_nn
```

## Running Scripts for generating plots and CSVs

**After the experiments have been completed, check that the `scripts/CSVs` folder contains `*.csv` files.**

- From the `scripts` folder (`code2inv/scripts`) run the following to generate CSVs and plots in the paper.

```bash
$ ./extract_run.sh
```

- For the plots run

```bash
$ ./plot.sh
```

## Details of Plots and CSVs generated

These folders and assets are generated in the `scripts` folder. 

- `CSVs (folder)` : We list the CSVs that are generated for running the scripts with appropriate `timeout`, `k-bounded` factor and `mode` of `Achar`. These CSVs are needed to generate the plots and tables shown the paper. 

```cpp
-- Achar returning All models, 10s timeout, K=64, 8 Epochs
compile_all_results_10_8_64.csv

-- Achar returning All models, 20s timeout, K=64, 8 Epochs
compile_all_results_20_8_64.csv

-- Achar returning single (first counterexample) model, 10s timeout, K=128
compile_results_10_8_128.csv

-- Achar returning single (first counterexample) model, 10s timeout, K=16
compile_results_10_8_16.csv

-- Achar returning single (first counterexample) model, 10s timeout, K=1 
compile_results_10_8_1.csv 

-- Achar returning single (first counterexample) model, 10s timeout, K=2
compile_results_10_8_2.csv 

-- Achar returning single (first counterexample) model, 10s timeout, K=32
compile_results_10_8_32.csv

-- Achar returning single (first counterexample) model, 10s timeout, K=64 (Baseline Setting)
compile_results_10_8_64.csv

-- Achar returning single (first counterexample) model, 20s timeout, K=64 
compile_results_20_8_64.csv

-- Achar returning single model (first counterexample) using Hybrid strategy
    where one statement in Loop body is a opaque operation , 10s timeout, K=64
compile_results_hybrid_loop_10_8_64.csv

-- Achar returning single model (first counterexample) using Hybrid strategy
    where one statement in Pre body is a opaque operation , 10s timeout, K=64
compile_results_hybrid_pre_10_8_64.csv

-- Code2Inv Base tool.
compile_results_z3_all_8.csv 
```
These plot PDFs are generated in the `scripts/plots` folder. 

- `plots/Time (Folder)` : The generated cactus plots for counterexamples vs instances solved for a given run of the tool on all 133 examples are stored in this folder.
	- `plots/Time/time_rq1.pdf` is the plot for `Achar vs. Code2Inv` for timing comparision. [Figure-4 from the paper]
	- `plots/Time/time_all_vs_one_instances.pdf` is the plot for `Solved vs. Time (All vs. One)`. [Figure-6 from the paper]
	- `plots/Time/time_hybrid.pdf` is the plot for `Achar Hybrid (Time)`. [Figure-7 from the paper]

- `plots/CEs (Folder)` : The generated cactus plots for time taken(secs) vs instances solved for a given run of the tool on all 133 examples are stored in this folder. 
	- `plots/CEs/ces_rq1.pdf` is the plot for `Achar vs. Code2Inv` (Cex) for counterexamples generated. [Figure-5 from the paper]
	- `plots/CEs/ces_hybrid.pdf` is the plot for `Achar Hybrid (Cex)` for counterexamples in case Achar is run in `Hybrid` mode. [Figure-8 from the paper]

- `data_summary.csv` : This generated file (in `scripts` folder) summarizes the log data (CSV files in `CSVs`) used in the tables shown in the paper and supplementary PDF. The CSV contains the following table which is used to fill the tables shown in the paper.

|Tool Setting        |#Solved|#Cex            |Time(secs) |Used in Table |
|--------------------|-------|----------------|-----------|--------------|
|Achar (All. 10s)    |100    |1779            |22156.0     |Table-7 Achar All Models (10s)|
|Achar (All. 20s)    |100    |1445            |30684.5     |Table-7 Achar All Models (20s)|
|Achar (Hybrid. Loop)|100    |1503            |7564.7     |Table-2 Achar-Hybrid (Loop)|
|Achar (Hybrid. Pre) |100    |1418            |7570.4     |Table-2 Achar-Hybrid (Pre)|
|Achar (K=1)         |97     |1337            |6728.5     |Table-8 (K=1) |
|Achar (K=2)         |97     |1257            |7730.0     |Table-8 (K=2) |
|Achar (K=16)        |97     |1280            |9957.0     |Table-8 (K=16) |
|Achar (K=32)        |98     |1295            |7822.4     |Table-8 (K=32) |
|Achar (K=64)        |100    |1416            |8587.0     |Table-2 Achar Base,Table-8 (K=64)|
|Achar (K=128)       |96     |1301            |10186.9    |Table-8 (k=128)|
|Achar (Single. 10s) |100    |1416            |8587.0     |Table-1 Achar (Correct)|
|Achar               |100    |1416            |8587.0     |Table-7 Achar Single Model (10s)|
|Achar (Single. 20s) |100    |1329            |8255.4     |Table-7 Achar Single Model (20s)|
|Code2Inv            |92     |1239            |3377.4     |Table-1 Code2Inv (Correct)|

# Previous Experimental results & Logs (Section-5 from the main paper)

The zip [Experimental_Logs](#Experimental_Logs.zip) contains the experimental logs and scripts (part of the artifact tar zip) needed to summarize the data and generate the plots presented in the paper. This is from the previous experiments we did inorder to evaluate Achar and presented the results in the accepted paper.The zip already contains the plots and CSV files used to summarize the tables and genrate the plots used in the paper and supplementary PDF.Please use a unix system (Eg. Ubuntu(18.04, 20.04)) to run the scripts.

`ACHAR_Experiments` folder contains all the experimental logs. (This is a huge folder and requires 6GB of hard-disk space.)

`datagen/scripts/data_summary.txt` : This generated file summarizes the log data used in the tables shown in the paper and supplementary PDF.

`datagen/scripts/CSVs` folder contains all the CSV files as described below.

```cpp
-- Achar returning All models, 10s timeout, K=64
compile_all_results_10_8_64.csv

-- Achar returning All models, 20s timeout, K=64
compile_all_results_20_8_64.csv

-- Achar returning single (first counterexample) model, 10s timeout, K=128
compile_results_10_8_128.csv

-- Achar returning single (first counterexample) model, 10s timeout, K=16
compile_results_10_8_16.csv

-- Achar returning single (first counterexample) model, 10s timeout, K=1 
compile_results_10_8_1.csv 

-- Achar returning single (first counterexample) model, 10s timeout, K=2
compile_results_10_8_2.csv 

-- Achar returning single (first counterexample) model, 10s timeout, K=32
compile_results_10_8_32.csv

-- Achar returning single (first counterexample) model, 10s timeout, K=64 (Baseline Setting)
compile_results_10_8_64.csv

-- Achar returning single (first counterexample) model, 20s timeout, K=64 
compile_results_20_8_64.csv

-- Achar returning single model (first counterexample) using Hybrid strategy
    where one statement in Loop body is a opaque operation , 10s timeout, K=64
compile_results_hybrid_loop_10_8_64.csv

-- Achar returning single model (first counterexample) using Hybrid strategy
    where one statement in Pre body is a opaque operation , 10s timeout, K=64
compile_results_hybrid_pre_10_8_64.csv

-- Code2Inv Base tool.
compile_results_z3_all_8.csv 
```

`datagen/scripts/CE_Data` & `datagen/scripts/Time_Data` contains the JSON files needed for generating the plots.

- We use the [mkplot](https://github.com/alexeyignatiev/mkplot) tool (with minor modifications) to generate the plots in the folder `plots\CEs` (counterexample plots) & `plots\Time` (Total Time plots).

- `ACHAR_Experiments\Summary` folder also contains all summarized data and JSON files for plotting.

- Running Scripts for generating plots and CSVs.

From the `scripts` folder run the following to generate CSVs and summary.

```bash
$ ./extract_run.sh
```

For the plots run

```bash
$ ./plot.sh
```

# Source and Transformed Code of the examples. 

The `benchmarks` folder contains the `P` and `P_cs` examples of the code used for evaluation in Achar.
These don't have the `P_Hat` template programs.
The `P_Hat` template programs can be accessed from the docker image which are under `code2inv/prog_generator/*` folder.
The mapping is as follows (from `P_cs` to corresponding `P_Hat` program source path)

- `benchmark/hybrid_loop` : code2inv/program_generator/HYBRID_LOOP/src
- `benchmark/hybrid_pre` : code2inv/program_generator/HYBRID_PRE/src
- `benchmark/Hybrid_Examples` : code2inv/program_generator/Hybrid_Examples/src (`multiply()` and `mod2check()` example)
- `benchmark/C_instances` : code2inv/program_generator/fuzz/src (All 133 benchmark examples)
- `benchmark/NN_Example` : code2inv/program_generator/NN_Example/src (CNN Example from section 5.1.2 of the main paper)

<div style="page-break-after: always;"></div>

# Running Docker.

Please pull and run the docker from the [acharver1/achar](https://hub.docker.com/r/acharver1/achar) docker registry.
The memory (`--memory`) and cpu (`--cpus`) values of the recommended settings have been shown below.

```bash
$ docker pull acharver1/achar:latest
$ docker run --name achar --cpus=4 --memory=16g -it acharver1/achar:latest
```

You will presented with a similar prompt from inside the docker if the above commands work properly.

```bash
root@aa1f567a2215:/achar#
```

Use the `runbench.sh` script for running the example. (See [Run a single example](#run-a-single-example))

```bash
root@aa1f567a2215:/achar# ./runbench.sh -h
    _        _
   / \   ___| |__   __ _ _ __
  / _ \ / __| '_ \ / _` | '__|
 / ___ \ (__| | | | (_| | |
/_/   \_\___|_| |_|\__,_|_|


==== Achar : Verifying REAL Loop Invariants. ====

Usage : ./runexample.sh (-h) [INDEX] [SPEC_TYPE] (Optional .. K-Induction Factor)
parameters :
  INDEX      Benchmark Example Number or Index to process.
  SPEC_TYPE  Specifiy the grammar and checker/solver pair for the run.
             Check the specs folder for more information

                 To run a Hybrid Benchmark {1..10} Example, spec : fuzz_hybrid
                 To run Open-Program Benchmark {1..12, 14, 15} Examples, spec : fuzz_open
                 To run the NN MNIST Example, spec : fuzz_nn, INDEX : 150
                 To run a Fuzz Example with HonggFuzz, spec : fuzz_spec, INDEX : [1-133]
                 To run with Z3, spec : c_nl_all_spec, INDEX : [1-133]
                 To run a Colassus Example, spec : colossus_spec [need Colossus Docker Running]


Examples :  Use the Example Number as INDEX.

      Hybrid Example 1 : multiply()
      Hybrid Example 2 : mod2check()

      Open-Program Benchmark Example 2 : isprime() // Paper Example [isprime()]
      Open-Program Benchmark Example 1 : sum() // Sum of squares
      Open-Program Benchmark Example 8 : multiply() // Multiply Example
  -h          Print this Help.

Example :
$ ./runbench.sh 11 fuzz_spec
```

## Running a single example from docker.

We show the command to run one(`example 11`) of the 133 benchmark example on Achar and code2inv tool. 

- `fuzz_spec` for `Achar` Tool.
- `c_nl_all_spec` for `Code2Inv` Tool.

```bash
root@aa1f567a2215:/achar# ./runbench.sh 11 fuzz_spec
root@aa1f567a2215:/achar# ./runbench.sh 11 c_nl_all_spec
```

## Running Additional Examples (Open-Program Examples)

We show the commands to run examples 1 and 5 from the Open Benchmarks that we have created.

```bash
root@aa1f567a2215:/achar# ./runbench.sh 1 fuzz_open
root@aa1f567a2215:/achar# ./runbench.sh 5 fuzz_open
```

Rest of the commands remain same as described in [Detailed Description](#detailed-description) section.

# Manual Installation

## Installation Steps (Resolving Dependencies)

We list out the dependencies and complete steps of installation for running the Achar tool. 
Extract the artifact and keep in directory of choice. (`\$HOME`). In the home directory (`\$HOME`), the following assets must be available. We list the commands to install and get things in place. We recommend running the following commands from the home directory (`\$HOME` dir). We provide a script `install.sh` to run all the commands in 
this section and prepare Achar tool for evaluation. We also list the steps here for completion. Set the `\$HOME` env variable appropriately instead of `\root` incase following these steps from inside a docker image. **\$HOME dir is same as the default ~ dir.**

- `clang`/`gcc/g++` compiler along with `python3` is required for Honggfuzz and Achar to work. 
`sudo` access is needed for installing the packages.

```bash
# Basic Setup requirements
$ sudo apt-get update && sudo apt-get install -y \
    python3 time python3-pip g++ gcc make cmake cmake-data git \
    wget unzip figlet lolcat clang-10 clang++-10 z3 \
    software-properties-common python-is-python3
```
Packages `figlet` and `lolcat` are optional but recommended to be installed.

- `HonggFuzz` Fuzzer framework. (`sudo` access is needed for installing the packages.)
We also a provide a zip of the `Honggfuzz` tool(`Honggfuzz-tool.zip`) in the `zenodo` artifact tar zip. It may be downloaded and used instead of the `git clone` command below.

```bash
# Set the $HOME variable to appropriately instead of \root
# incase using a fresh docker container to run.
cd $HOME

# HonggFuzz Dependencies
$ sudo apt-get install libbfd-dev libunwind8-dev

# Clone HonggFuzz
$ git clone https://github.com/google/honggfuzz.git
$ cd honggfuzz/

# Build it from source.
$ make 
$ sudo make install 
```

- In the home directory (\$HOME), download and unzip `libtorch`. 

We provided a zip `libtorch-shared-with-deps-latest.zip` in the `zenodo` artifact tar zip. It may be downloaded and extracted/unziped instead of the `wget` command below.

```bash
# Run from the $HOME directory.
$ cd $HOME

# Get the libtorch shared zip and unzip it.
$ wget https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip
$ unzip libtorch-shared-with-deps-latest.zip
```

## Setting up Achar Tool (using `patch_1.patch` patch provided)

We provide a binary diffed patch (`patch_1.patch`) that can be applied on the base `Code2Inv` repository. This converts `Code2Inv` tool to `Achar` tool. From any directory of choice, (prefereably \$HOME, ~ dir) run the following commands and apply the patch. Make sure the patch file `patch_1.patch` is kept in the \$HOME directory. 

```bash
$ git clone https://github.com/PL-ML/code2inv
$ cd code2inv
$ git apply ../patch_1.patch
```

- Now from this folder, run the following commands to install `Achar` tool dependencies. (folder where the artifact was extracted earlier.)

```bash
$ pip3 install datetime z3-solver scipy tqdm matplotlib seaborn
$ pip3 install -e .
```

# Extending the tool. 

The tool can be easily extended to a new backend instead of using `honggfuzz` to some other fuzzer or counterexample generator (see sections 5 and 6 from our main paper.). In-order to add a new backend, add a new checker and solver functions in  `code2inv/prog_generator/checkers` folder. A generic template is as given below, one needs to implement these two functions for the backend of choice and `code2inv` tool will run correctly with it. Check the [customizing.md](./customizing.md) file for more details. 

```python
# @params vc_file : contents of the VC file 
#   (verification conditions)
# @params inv : Learner proposed Invariant
# @params assignments : A dictonary containing values 
#   (assignments to program variables.)
def inv_checker(vc_file: str, inv: str, assignments):
    # RETURNS 
    # `True` if the Invariant(inv) is satisfied 
    # for the given assignments to program variables.
    
    # `False` if the Invariant(inv) is not satisfied 
    # for the given assignments to program variables.
    pass
```

```python
# Run the backend on the Invariant and generates counterexamples.
# @params vc_file : contents of the VC file (verification conditions)
# @params inv : Learner proposed Invariant
def inv_solver(vc_file: str, inv: str):
    # RETURNS 
    # Runs the counterexample generator backend
    # and returns a counterexamples if the invariant is not 
    # satisfied as a dictionary of program variables to 
    # values for which the invariant failed.
    
    # [None, None, None] if the Invariant(inv) is satisfiable
    # as shown by the backend run by this call.
    return []
```

We urge the reader to check the `structure` of the following files that we wrote as the `checker`, `solver` and `backend` interface files.

```
fuzzsolve_all_checker.py -- HonggFuzz Backend
fuzzsolve_checker.py -- HonggFuzz Backend
fuzzsolve_hybrid.py -- HonggFuzz Backend
fuzzsolve_nn.py -- HonggFuzz Backend
fuzzsolve_opaque.py -- HonggFuzz Backend
colossus_checker.py -- Colossus Tool Backend
```
