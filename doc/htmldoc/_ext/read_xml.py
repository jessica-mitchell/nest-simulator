import xml.etree.ElementTree as ET
import json


def process_xml(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()
    class_name = tree.find(".//ref").text

    for child in root:
        #print(child.tag, child.attrib)
        for grandchild in child:
            if grandchild == "detaileddescription":
                print("found it")
            print(grandchild.tag, grandchild.attrib)
# Find the text following the "DocKeywords" keyword
    doc_keywords_text = tree.find(".//para").text
    if doc_keywords_text and 'DocKeywords' in doc_keywords_text:
        keywords_start = doc_keywords_text.index('DocKeywords') + len('DocKeywords')
        keywords_list = doc_keywords_text[keywords_start:].strip().split(',')
        keywords = [keyword.strip() for keyword in keywords_list]
    else:
        keywords = []
    #    for simplesect in tree.getroot():
    #        print(simplesect)
    #        kind = simplesect.get('kind')
    #        if kind == 'class':
    #            name = simplesect.findtext('name')
    #            refid = simplesect.get('refid')
    #            print("name: :", name)
    #            print("refid: ", refid)
    print("Class Name:", class_name)
    print("Keywords:", keywords)
#   for para in tree.getroot():
#       text = para.text
#       if text and 'DocKeywords' in text:
#           keywords_start = text.index('DocKeywords') + len('DocKeywords')
#           keywords_list = text[keywords_start:].strip().split(',')
#           keywords = [keyword.strip() for keyword in keywords_list]
#       else:
#           keywords = []
#
#       print("Keywords:", keywords)
#
## Example usage
xml_file_path = "/home/mitchell/Work/build-repo/doc/doxygen/xml/classnest_1_1StimulationDevice.xml"
process_xml(xml_file_path)




