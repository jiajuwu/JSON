#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#define MY_ENCODING "UTF-8"

void modifyStory(xmlNodePtr cur)
{
    xmlChar *value = NULL;
    value = xmlNodeGetContent(cur);
    printf("content %s\n", value);
    xmlNodeSetContent(cur, (const xmlChar *)"192.168.15.22:4567");
    xmlFree(value);
}

void parseStory(xmlDocPtr doc, xmlNodePtr cur)
{
    xmlChar *key = NULL; 
    cur = cur->xmlChildrenNode;//IP_port and name
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"IP_port"))) {
            /*当我们找到元素"IP_port"时，
                        我们需要打印他包含在XML中的记录的内容，
                        文本被包含于元素的子结点中，因此我们借助了cur->xmlChildrenNode，
                        为了取得文本，我们使用函数xmlNodeListGetString，
                        他有一个文件指针参数，在这个例子中，我们仅仅打印他。 */
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("    IP_port: %s \n", key); 
            modifyStory (cur); 
            xmlFree(key); 
        }
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1); 
            printf("    name: %s \n", key); 
            xmlFree(key); 
        }
        cur = cur->next; 
    }
    return; 
}

int main(int argc, char **argv)
{
    xmlDocPtr doc = NULL;   //定义解析文档指针
    xmlNodePtr cur = NULL;  //定义结点指针(你需要它为了在各个结点间移动)
    xmlNodePtr child = NULL;
    xmlChar *key = NULL;
    char *psfilename = NULL;
    xmlChar *value = NULL;
#if 0
    if (argc < 1)
    {
        printf("error: Usage: %s filename/n" , argv[0]);
        return;
    }
    psfilename = argv[1];
#endif
    doc = xmlParseFile("w.xml"); 

    //doc = xmlReadFile(psfilename, MY_ENCODING, 256);  //解析文件
    if (doc == NULL )
    {
        fprintf(stderr,"Document not parsed successfully. \n");
        return;
    }

    cur = xmlDocGetRootElement(doc);  //确定文档根元素
    if (cur == NULL)/*检查确认当前文档中包含内容*/
    {
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc);
        return;
    }

    if (xmlStrcmp(cur->name, (const xmlChar *)"socket"))//roor node--socket
    {
        fprintf(stderr,"document of the wrong type, socket node != socket");
        xmlFreeDoc(doc);
        return;
    }
    printf("root node: %s\n", cur->name);

    cur = cur->xmlChildrenNode;//socket_type
    while(cur != NULL)
    {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"socket_type")))
        {
            value = xmlGetProp(cur, (const xmlChar *)"type");//attributeaa
            printf("socket_type: %s\n", value);
            parseStory(doc, cur);
            xmlFree(value);
        }
        cur = cur->next;
    }
    xmlSaveFormatFileEnc("w.xml", doc, "UTF-8", 1);
    xmlFreeDoc(doc);

    return(0);
}

