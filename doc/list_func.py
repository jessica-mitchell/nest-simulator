#!/bin/python

# Insert links (reST domain roles) to PyNest API functions and model names that are in the documentation
# Find the correct names of functions and models from source files
# Search restructured text files for those functions and models with specific markup and replace with proper link

import glob, os
import re
import ast

def replace_rst(k,v):
    for file in glob.glob("**/*.rst", recursive=True):
        for i, line in enumerate(open(file)):
               for match in re.finditer(k, line)
                   print(line.replace(k, v))

   def link_pyapi(functionNode):
       
       pynest_pattern = "``" + functionNode.name + "``"
       new_pynest_pattern = ":py:func:`." + functionNode.name + "`"
       get_rst(pattern, newpattern)
#       for file in glob.glob("**/*.rst", recursive=True):
#           for i, line in enumerate(open(file)):
       for match in re.finditer(pynest_pattern, line):
           print(line.replace(pynest_pattern, new_pynest_pattern))

   def link_model(cppModel):
       model_pattern = "``" + cppModel + "``"
       new_model_pattern = ":cpp:class:`" + cppModel + " <nest::" + cppModel + ">`"
#       for file in glob.glob("**/*.rst", recursive=True):
#           for i, line in enumerate(open(file)):
               for match in re.finditer(model_pattern, line):
                   print(line.replace(model_pattern, new_model_pattern))

   def link_term(item):
       gloss_pattern = "``" + item + "``"
       new_gloss_pattern = ":term:`" + item + "`"
#       for file in glob.glob("**/*.rst", recursive=True):
#           for i, line in enumerate(open(file)):
       for match in re.finditer(gloss_pattern, line):
           print(line.replace(gloss_pattern, new_gloss_pattern))

for file in glob.glob("../pynest/nest/lib/*.py"):
    with open(file) as f:
        node = ast.parse(f.read())
        functions = [n for n in node.body if isinstance(n, ast.FunctionDef)]
        for function in functions:
             link_pyapi(function)

key = re.compile('^class')

for file in glob.glob("../models/*.h"):
    for i, line in enumerate(open(file)):
            if key.match(line):
                i = str(i)
                models = [line.split(' ')[1]]
                for model in models:
                    link_model(model)

glossary_terms = re.compile('^ [a-zA-Z]')

with open('glossary.rst') as file:
    for line in file
    if glossary_terms.match(line):
        terms = [line]
        for term in terms:
             link_term(gloss)

