import os
import sys
import argparse
import errno
import json

#path = "/home/mitchell/Work/repo/nest-simulator/doc/htmldoc/_doxygen/xml/"
#index = xml.etree.ElementTree.parse(os.path.join(path, "DocKeywords.xml"))
#root = index.getroot()
from collections import defaultdict
from docutils import nodes
from docutils.parsers.rst import Directive

import xml.etree.ElementTree as ET

def extract_data_from_xml(file_path):
    tree = ET.parse(file_path)
    root = tree.getroot()
    ref_list = []
    term_list = []
    para_list = []

    varlist_entries = root.findall('.//varlistentry')
    item_entries = root.findall('.//listitem')
    for entry in varlist_entries:
        ref_element = entry.find('.//ref')
        term_element = entry.find('.//term')

        if ref_element is not None:
            ref_text = ref_element.text.strip()
            ref_list.append(ref_text)

        if term_element is not None:
            term_text = term_element.text.strip()
            term_list.append(term_text)

    for listitem in item_entries:
        para_text_list = []
        para_elements = listitem.findall('.//para')
        for para_element in para_elements:
            for text in para_element.itertext():
                para_text = text.split()
                if para_text:
                    para_list.append(para_text)

    return ref_list, term_list, para_list

# Example usage
file_path = '_doxygen/xml/DocKeywords.xml'

ref_list, term_list, para_list = extract_data_from_xml(file_path)

zipped_kw = zip(ref_list, term_list, para_list)
dict_kw = dict(zip(ref_list, para_list))
list_kw = list(zipped_kw)
print("dict original; ", dict_kw)
#print(all_dict)

# reverse the list
res = defaultdict(list)
for keys, values in dict_kw.items():
    for value in values:
        res[value].append(keys)

rev_dict = str(dict(res))
print(rev_dict)

#print("Ref List:", ref_list)
#print("Term List:", term_list)
# Using the rev_dict
# create a doxygen directive
#for key, values in rev_dict.iter():


