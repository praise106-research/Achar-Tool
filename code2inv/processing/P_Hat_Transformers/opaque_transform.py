#!/usr/bin/python3

# We manually annotate the code as per the template below and then
# we can run the code to generate P-Hat Trasnformation for P_Hat generation.

import sys
import os

abc = sys.argv[1].strip()
fileName = sys.argv[2].strip()

if ";" in abc:
    varList = [str(v.strip()) for v in sys.argv[1].strip().split(";")]
else:
    varList = [str(v.strip()) for v in sys.argv[1].strip().split()]

while "" in varList:
    varList.remove("")


def pre(arglist="", formatString="", arglistString="", varlistString=""):
    PreTemplate = "// COMMENT : Precheck function \n"
    PreTemplate += f"void precheck(FILE *fptr, char *modelFileBuffer, {arglist})\n"
    PreTemplate += "{\n"
    PreTemplate += "    int f = preflag;"
    PreTemplate += f"   setflag(INV({arglistString}), preflag); \n"
    PreTemplate += "    if (f == 0 && preflag == 1){\n"
    PreTemplate += (
        f'       fprintf(fptr, "Pre : {formatString}\\n", \n {varlistString});\n'
    )
    PreTemplate += "\nassert(0);\n}}\n\n"
    return PreTemplate


def loop(
    arglist="",
    formatString="",
    arglistString="",
    varlistString="",
    looptemplist="",
    loopargsString="",
):
    loopTemplate = "// COMMENT : Loopcheck function \n"
    loopTemplate += f"void loopcheck(FILE *fptr, char *modelFileBuffer, {looptemplist}, {arglist})\n"
    loopTemplate += "{\n"
    loopTemplate += "    int f = loopflag;\n"
    loopTemplate += f"   setflag(INV({arglistString}), loopflag); \n"
    loopTemplate += "    if (f == 0 && loopflag == 1){\n"
    loopTemplate += (
        f'       fprintf(fptr, "LoopStart : {formatString}\\n", \n {loopargsString});\n'
    )
    loopTemplate += (
        f'       fprintf(fptr, "LoopEnd : {formatString}\\n", \n {varlistString});\n'
    )
    loopTemplate += "\nassert(0);\n}}\n\n"
    return loopTemplate


def post(arglist="", formatString="", arglistString="", varlistString=""):
    postTemplate = "// COMMENT : Postcheck Macro \n"
    postTemplate += (
        f"#define postcheck(fptr, modelFileBuffer, cond, {arglistString})\ \n")
    postTemplate += "{\ \n"
    postTemplate += "    int f = postflag;\ \n"
    postTemplate += f"   setflag(cond, postflag);\ \n"
    postTemplate += "    if (f == 0 && postflag == 1){\ \n"
    postTemplate += f'        fprintf(fptr, "Post : {formatString}\\n", \ \n {varlistString}); assert(0);\ \n'
    postTemplate += "}}\n\n"
    return postTemplate


pwd = os.path.dirname(__file__)
sourcepath = sys.argv[3]
sourcefile = os.path.join(sourcepath, f"{fileName}.c")
includefile = os.path.join(f"include/{fileName}.h")
loopcheckfile = os.path.join(f"src/{fileName}.c")

if __name__ == "__main__":
    arglist = ""
    varlistString = ""
    formatString = ""
    arglistString = ""
    linkerArgsString = "choices, "
    looptemplist = ""
    loopargsString = ""
    loopvarListstr = ""
    loopTermTerms = ""
    printformatString = "%lld, "
    externArgs = "long long int, "

    with open(sourcefile, mode="r") as fileptr:
        code = fileptr.readlines()

    with open(includefile, mode="w") as fileptr:
        fileptr.write(f"#define PHI 1 // generated by code2inv \n")

    for index, v in enumerate(varList):
        varlistString += f"{v}, "
        
    HonggFuzzInputLines = []
    variablesDecl = []
    preconditions = []
    loopbody = []
    postcondition = []
    preMainText = []
    appendInit = []
    condString = "(choices > 2500)"

    index = 0
    scanf = 0
    lines = code[index]

    for r, line in enumerate(code):
        if "int main()" in line.strip():
            index = r
            break
        preMainText.append(line.strip())

    lines = code[index]

    while index < len(code):
        lines = lines.strip()

        if "/*" in lines:
            while "*/" not in lines:
                index = index + 1
                lines = code[index]

        if "*/" in lines:
            index = index + 1
            lines = code[index]

        if "int main()" in lines:
            index = index + 1
            lines = code[index]

        if "variable declarations" in lines:
            while "pre-conditions" not in lines:
                if "int " in lines:
                    lines = f"long long {lines.strip()}"
                    variablesDecl.append(lines)
                else:
                    appendInit.append(lines.strip())
                index = index + 1
                lines = code[index]

        if "pre-conditions" in lines:
            while "precheck" not in lines:
                if "scanf" in lines:
                    scanf += 1
                    line = f"long long int {lines.split('&')[-1].strip()[0:-2]} = honggBuf[{scanf}];"
                    HonggFuzzInputLines.append(line)
                    lines = ""
                preconditions.append(lines)
                index = index + 1
                lines = code[index]

        if "precheck" in lines:
            index = index + 1
            lines = code[index]

        if "loopcond" in lines:
            condString = lines.split(":")[-1].strip()
            if "unknown" in condString:
                condString = "(choices > 2500)"
            index = index + 1
            lines = code[index]

        if "loopstart" in lines:
            index = index + 1
            lines = code[index]

        if "while" in lines:
            index = index + 1
            lines = code[index]
            loopbody.append("{ \n")

        if "loop body" in lines:
            while "loopend" not in lines:
                if "unknown" in lines:
                    lines = "// non-deterministic \n if (choices > 3500) {"
                loopbody.append(lines)
                index = index + 1
                lines = code[index]

        if "loopend" in lines:
            index = index + 1
            lines = code[index]

        if "postcheck" in lines:
            index = index + 1
            lines = code[index]

        if "post-condition" in lines:
            while index < len(code) - 1:
                if "assert" in lines:
                    assertCond = lines.split("assert")[-1].strip()
                    lines = f"""
                                postcheck(fptr, vars, {assertCond.strip()[:-1]}, {varlistString.strip()[:-1]})
                            """
                postcondition.append(lines.strip())
                index = index + 1
                lines = code[index]

        index = index + 1

    HonggFuzzInputLines = []
    for index, v in enumerate(varList):
        loopvarListstr += f"temp_{v}, "
        arglist += f"long long int {v}, "
        looptemplist += f"long long int temp_{v}, "
        formatString += "%s : %lld, "
        printformatString += "%lld, "
        arglistString += f'"{v}", {v}, '
        externArgs += f"long long int &, "
        linkerArgsString += f"{v}, "
        loopargsString += f'"{v}", temp_{v}, '
        loopTermTerms += f"long long int temp_{v} = {v};\n"
        line = f"long long int {v} = honggBuf[{index}];"
        HonggFuzzInputLines.append(line.strip())
        
    newline = "\n"
    preconditions.pop(0)
    loopbody = f"\n{newline.join([x.strip() for x in loopbody])}"
    prebody = f"\n{newline.join([x.strip() for x in preconditions])}"
    HonggFuzzInputLinesSTR = f"{newline.join([x.strip() for x in HonggFuzzInputLines])}"
    postbody = f"\n{newline.join([x.strip() for x in postcondition])}"
    preMainBody = f"\n{newline.join([x.strip() for x in preMainText])}"
    valDecl = f"\n{newline.join([x.strip() for x in variablesDecl])}"
    initLines = f"\n{newline.join([x.strip() for x in appendInit])}"

    K = 64
    
    template = f"""
        /*
        * P-Hat Transformation 
        * Loopbody and prebody opaque
        * Post is trivial so nothing to make opaque
        * for {fileName}.c file
        */

        # include <{fileName}.h>
        # include <assert.h>
        # include <inttypes.h>
        # include <libhfuzz/libhfuzz.h>
        # include <stdarg.h>
        # include <stdio.h>
        # include <stdlib.h>
        # include <math.h>
        # include <sys/file.h>
        # include <string.h>
        
        {preMainBody}

        # define UNROLL_LIMIT {K}
        
        # define setflag(cond, flag) if (!(cond)) flag = 1;

        # define assume(cond) if (!(cond)) continue;

        # define INV({varlistString.strip()[:-1]}) PHI

        extern void prebody_f1({externArgs.strip()[:-1]});
    
        extern void loopbody_f2({externArgs.strip()[:-1]});

        long long unsigned int counter = 0;
        int preflag = 0, loopflag = 0, postflag = 0;
        long long unsigned int precount = 0, loopcount = 0, postcount = 0;

        {pre(arglist.strip()[:-1],
                formatString.strip()[:-1],
                varlistString.strip()[:-1],
                arglistString.strip()[:-1])}
        
        {loop(arglist.strip()[:-1],
                formatString.strip()[:-1],
                varlistString.strip()[:-1],
                arglistString.strip()[:-1],
                looptemplist.strip()[:-1],
                loopargsString.strip()[:-1])}
        
        {post(arglist.strip()[:-1],
                formatString.strip()[:-1],
                varlistString.strip()[:-1],
                arglistString.strip()[:-1])}

        int main(int argc, char* *argv) {{
            // variable declarations
            #ifndef READ_FROM_FLAG
                {valDecl}
            #endif
            
            {initLines}

            // Buffered File stream.
            char modelFileBuffer[2048];
            memset(modelFileBuffer, '\0', sizeof(modelFileBuffer));
            FILE *fptr = fopen("models.txt", "w");
            setvbuf(fptr, modelFileBuffer, _IOLBF, 2048);

            FILE *inputs = fopen("inputs/inputs_{fileName}.txt", "a");
            setvbuf(inputs, modelFileBuffer, _IOLBF, 2048);

            #ifdef READ_FROM_FLAG
                fprintf(fptr, "Checker : {formatString.strip()[:-1]}\\n", 
                    {arglistString.strip()[:-1]});\n
                if(INV({varlistString.strip()[:-1]})) {{
                    fprintf(fptr, "True\\n");
                }} else {{
                    fprintf(fptr, "False\\n");
                }}
                assert(0);
            #endif

            int reach_flag = 0;
            for (;;) {{
                // Initialize HonggFuzz
                size_t len;
                const int16_t *honggBuf;
                HF_ITER(&honggBuf, &len);
                counter++;

                // Populate with Inputs
                long long int choices = honggBuf[10];

                #ifndef READ_FROM_FLAG
                    {HonggFuzzInputLinesSTR}
                #endif

                char vars[128];
                memset(vars, '\0', sizeof(vars));
                snprintf(vars, 128, "{formatString.strip()[:-1]}\\n", 
                    {arglistString.strip()[:-1]});

                fprintf(inputs, "{printformatString.strip()[:-1]}\\n", 
                    {varlistString.strip()[:-1]}, choices);

                // Translate()
                if (choices > 10000) {{
                    prebody_f1({linkerArgsString.strip()[:-1]});\n
                    precount++;
                    // fprintf(fptr, "Pre\\n");
                    // precheck
                    precheck(fptr, vars, 
                        {varlistString.strip()[:-1]});
                }} else {{

                    // loop-check program
                    assume((loopflag + postflag < 2));
                    assume(INV({varlistString.strip()[:-1]}));

                    // Loop Condition
                    if ({condString}) {{
                        // K-Bounded Exploration
                        int unroll = UNROLL_LIMIT;
                        while ({condString} && unroll--) {{
                            assume((loopflag == 0));
                                {loopTermTerms}
                                loopbody_f2({linkerArgsString.strip()[:-1]});\n
                            
                            // fprintf(fptr, "Loop\\n");
                            // fprintf(fptr, "Flag : %d\\n", reach_flag);
                            // assume(reach_flag);
                            
                            loopcount++;
                            loopcheck(fptr, vars, 
                                {loopvarListstr.strip()[:-1]}, 
                                {varlistString.strip()[:-1]});
                        }}
                    }} else {{
                        // post-check program
                        assume((postflag == 0));
                        postcount++;
                        // fprintf(fptr, "Post\\n");
                        {postbody}
                    }}
                }}

                // Print the counters if no flags are hit
                if (preflag + loopflag + postflag == 0 && counter == 100) {{
                    fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld[newline]", 
                        "precount", precount, "loopcount", loopcount, "postcount", postcount);
                    counter = 0;
                }}

                // Close FILE with assert(0); 
                if (preflag + loopflag + postflag >= 3) {{
                    fclose(fptr);
                    assert(0);
                }}
            }}

            // Regular Close FILE 
            fclose(fptr);
            return 0;
        }}
    """
    print(template.replace("[newline]", "\\n").replace("\0", "\\0"))
