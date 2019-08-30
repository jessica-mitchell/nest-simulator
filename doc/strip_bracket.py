import os
import glob
import ast

def replace_functionName(old, new):
    file_out = "tmp.rst"
    for file in glob.glob("**/*.rst", recursive=True):
        with open(file) as fin:
            with open(file_out, "wt") as fout:
                for line in fin:
                     fout.write(line.replace(old, new))
        os.rename(file_out, file)

def link_pyapi(functionNode):
    pynest_pattern = "``" + functionNode.name + "()``"
    new_pynest_pattern = "``" + functionNode.name + "``"
    replace_functionName(pynest_pattern, new_pynest_pattern)

for file in glob.glob("../pynest/nest/lib/*.py"):
    with open(file) as f:
        node = ast.parse(f.read())
        functions = [n for n in node.body if isinstance(n, ast.FunctionDef)]
        for function in functions:
             link_pyapi(function)

