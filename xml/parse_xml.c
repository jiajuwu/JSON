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
            /*�������ҵ�Ԫ��"IP_port"ʱ��
                        ������Ҫ��ӡ��������XML�еļ�¼�����ݣ�
                        �ı���������Ԫ�ص��ӽ���У�������ǽ�����cur->xmlChildrenNode��
                        Ϊ��ȡ���ı�������ʹ�ú���xmlNodeListGetString��
                        ����һ���ļ�ָ�����������������У����ǽ�����ӡ���� */
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
    xmlDocPtr doc = NULL;   //��������ĵ�ָ��
    xmlNodePtr cur = NULL;  //������ָ��(����Ҫ��Ϊ���ڸ��������ƶ�)
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

    //doc = xmlReadFile(psfilename, MY_ENCODING, 256);  //�����ļ�
    if (doc == NULL )
    {
        fprintf(stderr,"Document not parsed successfully. \n");
        return;
    }

    cur = xmlDocGetRootElement(doc);  //ȷ���ĵ���Ԫ��
    if (cur == NULL)/*���ȷ�ϵ�ǰ�ĵ��а�������*/
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

