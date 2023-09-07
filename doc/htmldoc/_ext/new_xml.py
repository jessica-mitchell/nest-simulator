import xml.etree.ElementTree as ET

xml_file_path = "/home/mitchell/Work/build-repo/doc/doxygen/xml/DocKeywords.xml"
# Parse the XML string
tree = ET.parse(xml_file_path)
root = tree.getroot()
# Find the <para> elements and extract their text while excluding <anchor> elements
text_list = []
mydict = {}
for compound in root.findall(".//ref"):
    if "::" in compound.text:
        my_class = compound.text
    for listitem in root.findall(".//listitem"):
        for para_element in listitem.findall(".//para"):
            text = "".join(para_element.itertext()).strip()
            list_keywords = text.split(",")
            mydict[my_class] = list_keywords

reverse_dict = {}
for key, values in mydict.items():
    for value in values:
        reverse_dict.setdefault(value, []).append(key)

print(reverse_dict)


# Filter out empty strings


# import xml.etree.ElementTree as ET
#
## Define the path to your XML file
#
# xml_string = '<para><anchor id="DocKeywords_1_DocKeywords000013"/> stimulation, anotherone  </para>'
#
## Parse the XML string
# string_root = ET.fromstring(xml_string)
#
## Extract the text from the <para> element excluding the <anchor> element
# text = ''.join(string_root.itertext()).strip()
# print(text)
#
## Parse the XML file
# tree = ET.parse(xml_file_path)
# root = tree.getroot()
#
# for compound in root.findall(".//ref"):
#    print(compound.text)
#
#
##for words in root.findall(".//para"):
##    print(words.text)
## Initialize a dictionary to store the key-value pairs
# data_dict = {}

# Iterate through varlistentry elements
#    # Find the text inside the <ref> section
#    ref_text_element = varlistentry.find(".//ref")
#    if ref_text_element is not None:
#        ref_text = ref_text_element.text.strip()
#
#        # Find the text inside the corresponding <listitem>
#        #for listitem in root.findall(".//listitem"):
#            #listitem_element = listitem.find(".//para")
#            #for para in listitem.findall(".//para"):
#           #     if para.text is not None:
#           # if listitem is not None:
#           #     listitem_text = ' '.join([para.text.strip() for para in listitem.findall(".//para") if para.text is not None])
#           # else:
#           #     listitem_text = ""
#
#            # Add the data to the dictionary
#            #data_dict[ref_text] = listitem_text
#   #    data_dict[ref_text] = para
#
## Print the dictionary
# for key, value in data_dict.items():
#    print(f"Key: {key}")
#    print(f"Value: {value}")
#    print()
#
## To access a specific entry by key:
# specific_entry = data_dict.get("nest::IOManager")
# print(f"Specific Entry: {specific_entry}")
