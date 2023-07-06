import os
import sys
import argparse
import errno
import xml.etree.ElementTree
import json



# Run doxygen
# Store xml files
# Get the list of keywords and use as key and value as the class name
# directive .. keyword:: io - list all classes with io
#def write_file(name):
##    """Write the output file for module/package <name>."""
#    destdir = "../"
#    fname = os.path.join(destdir, "%s.rst" % name)
#    print("Creating file %s." % fname)
#    if not os.path.exists(os.path.dirname(fname)):
#        try:
#            os.makedirs(os.path.dirname(fname))
#        except OSError as exc:  # Guard against race condition
#                if exc.errno != errno.EEXIST:
#                    raise
#    try:
#        with open(fname, "r") as target:
#            orig = target.read()
#            if orig == name:
#                print("File %s up to date, skipping." % fname)
#                return
#    except FileNotFoundError:
#        # Don't mind if it isn't there
#        pass
##
#    with open(fname, "w") as target:
#        target.write(name)
#
#def recurse_tree(args):
#    """
#    Look for every file in the directory tree and create the corresponding
#    ReST files.
#    """
rootpath = "/home/mitchell/Work/build-repo/doc/doxygen/xml/"
index = xml.etree.ElementTree.parse(os.path.join(rootpath, "classnest_1_1StimulationDevice.xml"))
root = index.getroot()
#
#    # Assuming this is a valid Doxygen XML

#for para in index.iter():
 #   if para.findtext("DocKeywords"):
        #print(para.text)

for para in index.iter():
    result = para.findtext("DocKeywords")
    #result = para.get("DocKeywords")
    if result is not None:
        print("find doc keywords: ", result)

for para in index.iter():
    if para.tag == "DocKeywords":
        print(para.text)
      #  for child in root:
      #      for grandchild in child:
      #          for greatgrandchild in grandchild:
      #              for greatgreatgrandchild in greatgrandchild:
      #                  if greatgrandchild.tag == "para":
      #                      print(greatgreatgrandchild.tag, greatgrandchild.tag, grandchild.tag)
  
   #if "DocKeywords" in result.text:
   #     print("found it")
   #     print(result.text)


for para in index.getroot():
    package = para.findtext("Stimulation")
    package_type = para.get("kind")
    package_id = para.get("refid")

    #if package.startswith("nest::"):

    #print(package, package_id)
        #write_file(os.path.join(package_type, package_id))
#def process_xml(xml_file):
#    tree = ET.parse(xml_file)
#    root = tree.getroot()
#    class_name = tree.find(".//ref").text
#
#    for child in root:
#        #print(child.tag, child.attrib)
#        for grandchild in child:
#            if grandchild == "detaileddescription":
#                print("found it")
#            print(grandchild.tag, grandchild.attrib)
## Find the text following the "DocKeywords" keyword
#    doc_keywords_text = tree.find(".//para").text
#    if doc_keywords_text and 'DocKeywords' in doc_keywords_text:
#        keywords_start = doc_keywords_text.index('DocKeywords') + len('DocKeywords')
#        keywords_list = doc_keywords_text[keywords_start:].strip().split(',')
#        keywords = [keyword.strip() for keyword in keywords_list]
#    else:
#        keywords = []
#    #    for simplesect in tree.getroot():
#    #        print(simplesect)
#    #        kind = simplesect.get('kind')
#    #        if kind == 'class':
#    #            name = simplesect.findtext('name')
#    #            refid = simplesect.get('refid')
#    #            print("name: :", name)
#    #            print("refid: ", refid)
#    print("Class Name:", class_name)
#    print("Keywords:", keywords)
##   for para in tree.getroot():
##       text = para.text
##       if text and 'DocKeywords' in text:
##           keywords_start = text.index('DocKeywords') + len('DocKeywords')
##           keywords_list = text[keywords_start:].strip().split(',')
##           keywords = [keyword.strip() for keyword in keywords_list]
##       else:
##           keywords = []
##
##       print("Keywords:", keywords)
##
### Example usage
#process_xml(xml_file_path)




