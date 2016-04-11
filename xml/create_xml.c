#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main(int argc, char **argv)
{
     xmlDocPtr doc = NULL;       //文件指针
     xmlNodePtr root_node = NULL;
     xmlNodePtr sk_node = NULL, ipport_node = NULL;//节点指针
     xmlNodePtr dm_node = NULL, name_node = NULL;//节点指针

     // 创建一个文件，以及设置一个根节点
     doc = xmlNewDoc(BAD_CAST "1.0");
     root_node = xmlNewNode(NULL, BAD_CAST "socket");
     xmlDocSetRootElement(doc, root_node);

     //创建一个绑定在根节点的子节点     
     sk_node = xmlNewNode(NULL, BAD_CAST "socket_type");
     xmlNewProp(sk_node, BAD_CAST "type", BAD_CAST "common");
     xmlAddChild(root_node, sk_node);

     ipport_node = xmlNewChild(sk_node, NULL, BAD_CAST "IP_port", BAD_CAST"192.168.15.22:1234");
     ipport_node = xmlNewChild(sk_node, NULL, BAD_CAST "IP_port", BAD_CAST"192.168.15.22:2345");

     //通过xmlNewProp()增加一个节点的属性
     dm_node = xmlNewNode(NULL, BAD_CAST "socket_type");
     xmlNewProp(dm_node, BAD_CAST "type", BAD_CAST "domain");
     xmlAddChild(root_node, dm_node);

     //创建节点的另一种方法
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

