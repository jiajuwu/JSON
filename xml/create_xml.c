#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main(int argc, char **argv)
{
     xmlDocPtr doc = NULL;       //�ļ�ָ��
     xmlNodePtr root_node = NULL;
     xmlNodePtr sk_node = NULL, ipport_node = NULL;//�ڵ�ָ��
     xmlNodePtr dm_node = NULL, name_node = NULL;//�ڵ�ָ��

     // ����һ���ļ����Լ�����һ�����ڵ�
     doc = xmlNewDoc(BAD_CAST "1.0");
     root_node = xmlNewNode(NULL, BAD_CAST "socket");
     xmlDocSetRootElement(doc, root_node);

     //����һ�����ڸ��ڵ���ӽڵ�     
     sk_node = xmlNewNode(NULL, BAD_CAST "socket_type");
     xmlNewProp(sk_node, BAD_CAST "type", BAD_CAST "common");
     xmlAddChild(root_node, sk_node);

     ipport_node = xmlNewChild(sk_node, NULL, BAD_CAST "IP_port", BAD_CAST"192.168.15.22:1234");
     ipport_node = xmlNewChild(sk_node, NULL, BAD_CAST "IP_port", BAD_CAST"192.168.15.22:2345");

     //ͨ��xmlNewProp()����һ���ڵ������
     dm_node = xmlNewNode(NULL, BAD_CAST "socket_type");
     xmlNewProp(dm_node, BAD_CAST "type", BAD_CAST "domain");
     xmlAddChild(root_node, dm_node);

     //�����ڵ����һ�ַ���
     name_node = xmlNewChild(dm_node, NULL, BAD_CAST "name", BAD_CAST"cl_domain_socket");
     name_node = xmlNewChild(dm_node, NULL, BAD_CAST "name", BAD_CAST"co_domain_socket");

     //save the xml file
     xmlSaveFormatFileEnc("w.xml", doc, "UTF-8", 1);

     /*free the document */
     xmlFreeDoc(doc);
     xmlCleanupParser();
     xmlMemoryDump();//debug memory for regression tests

     return(0);
}

