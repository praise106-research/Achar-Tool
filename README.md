# Getting Started

Install and run Achar tool.

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