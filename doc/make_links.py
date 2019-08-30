# -*- coding: utf-8 -*-
#
# make_links.py
#
# This file is part of NEST.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################################################

# Insert links (reST roles) to PyNest API functions, model names and glossary items that are in the documentation
# Find the correct names of functions and models from source files
# Search restructured text files for those functions and models with specific markup and replace with proper link

import glob, os
import re
import ast

# Replace the keyword match found in docs with the restructered text mark up version to create the link
def replace_rst(k,v):
    file_out = "tmp.rst"

    for file in glob.glob("**/*.rst", recursive=True):
        with open(file, "rt") as fin:
            with open(file_out, "wt") as fout:
    #            for i, line in enumerate(fin):
                for line in fin:
                    if k in line:
                        print("Filename:" + file + "\n" + line)
                    fout.write(line.replace(k,v))
        os.rename(file_out, file)
            # if k in line:
            #     print(line.replace(k, v))
        #close(file)
# Create the pattern for finding match and replacing it with correct syntax
def link_pyapi(functionNode):
    pynest_pattern = "``" + functionNode.name + "``"
    new_pynest_pattern = ":py:func:`." + functionNode.name + "`"
    replace_rst(pynest_pattern, new_pynest_pattern)

def link_model(cppModel):
    model_pattern = "``" + cppModel + "``"
    new_model_pattern = ":cpp:class:`" + cppModel + " <nest::" + cppModel + ">`"
    replace_rst(model_pattern, new_model_pattern)

def link_term(item):
    gloss_pattern = "``" + item + "``"
    new_gloss_pattern = ":term:`" + item + "`"
    replace_rst(gloss_pattern, new_gloss_pattern)

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
    for line in file:
        if glossary_terms.match(line):
            terms = [line.strip()]
            for term in terms:
                 link_term(term)

