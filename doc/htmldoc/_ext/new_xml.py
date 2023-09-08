from sphinx.application import Sphinx
from docutils import nodes
import xml.etree.ElementTree as ET


def getClassXML():
    xml_index = "/home/mitchell/Work/build-repo/doc/doxygen/xml/index.xml"

    tree2 = ET.parse(xml_index)
    root2 = tree2.getroot()
    # Find the <para> elements and extract their text while excluding <anchor> elements
    mydict2 = {}

    classes = []
    for compound in root2.findall("compound"):
        kind = compound.get("kind")
        refid = compound.get("refid")
        if kind == "class" and "NestModule" not in refid and "DummyNode" not in refid:
            thing = compound.find("name").text
            classes.append(thing)
            # Create a rst page for each thing
    return classes


def extractFromXML():
    xml_file_path = "/home/mitchell/Work/build-repo/doc/doxygen/xml/DocKeywords.xml"

    # Parse the XML file
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

    return reverse_dict


def CreateCPPdocs(app):
    class_list = getClassXML()

    for item in class_list:
        if "nest::" in item:
            filename = item[6:]
        else:
            filename = item

        text = item + "\n\n"
        text += ".. doxygenclass:: " + item + "\n"

        with open("cppDocs_{}.rst".format(filename.strip()), "w") as f:
            f.write(text)

        CreateIndex(filename)


def CreateIndex(filename):
    keyword_dict = extractFromXML()
    for key, values in keyword_dict.items():
        # Create a reST title node
        text = "Keyword: " + key + "\n\n"
        # title_node = nodes.title()

        for value in values:
            if filename in value:
                text += ".. toctree::" + "\n\n"
                text += "  " + value + " <" + filename + ">\n"

            # para_node = nodes.paragraph(text=text)

            # Create a reST paragraph node with your desired content
            #    paragraph_node = nodes.paragraph()
            # paragraph_node.append(nodes.Text(mytext))

            # Create a reST document node and add the title and paragraph
            # doc_node += title_node
            # doc_node += paragraph_node

            # Serialize the document node to reST
            # rst_content = paragraph_node
            # rst_content = doc_node.pformat()

            # print("RST CONTENT: ", rst_content)
            with open("cppKeywords_{}.rst".format(key.strip()), "w") as f:
                f.write(text)


# def CreateIndex()
#
#    for each keywords create an element that
#    links to the page
#
# def ByKeywords(app, docname, source):
#    if docname == "test-breathepage":
#        keyword_classes = extractFromXML()
#        html_context = {"cpp_dict": keyword_classes}
#        new_source = source[0]
#        rendered = app.builder.templates.render_string(new_source, html_context)
#        source[0] = rendered
#
#


def setup(app):
    # app.connect("source-read", ByKeywords)
    app.connect("builder-inited", CreateCPPdocs)

    return {"version": "0.1", "parallel_read_safe": True, "parallel_write_safe": True}
