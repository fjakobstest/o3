#ifdef O3_WITH_GLUE
#pragma warning( disable : 4100)
#pragma warning( disable : 4189)
namespace o3 {


Trait* cXmlNode1::select()
{
   return clsTraits();
}

Trait* cXmlNode1::clsTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cXmlNode1",          0,                    0,              0,      cScr::clsTraits()  },
         {      0,      Trait::TYPE_FUN,        "cXmlNode1",          "replaceNode",        clsInvoke,      0,      0                  },
         {      1,      Trait::TYPE_GET,        "cXmlNode1",          "xml",                clsInvoke,      1,      0                  },
         {      2,      Trait::TYPE_GET,        "cXmlNode1",          "nodeName",           clsInvoke,      2,      0                  },
         {      3,      Trait::TYPE_GET,        "cXmlNode1",          "nodeValue",          clsInvoke,      3,      0                  },
         {      3,      Trait::TYPE_SET,        "cXmlNode1",          "nodeValue",          clsInvoke,      4,      0                  },
         {      4,      Trait::TYPE_GET,        "cXmlNode1",          "nodeType",           clsInvoke,      5,      0                  },
         {      5,      Trait::TYPE_GET,        "cXmlNode1",          "parentNode",         clsInvoke,      6,      0                  },
         {      6,      Trait::TYPE_GET,        "cXmlNode1",          "childNodes",         clsInvoke,      7,      0                  },
         {      7,      Trait::TYPE_GET,        "cXmlNode1",          "firstChild",         clsInvoke,      8,      0                  },
         {      8,      Trait::TYPE_GET,        "cXmlNode1",          "lastChild",          clsInvoke,      9,      0                  },
         {      9,      Trait::TYPE_GET,        "cXmlNode1",          "previousSibling",    clsInvoke,      10,     0                  },
         {      10,     Trait::TYPE_GET,        "cXmlNode1",          "nextSibling",        clsInvoke,      11,     0                  },
         {      11,     Trait::TYPE_GET,        "cXmlNode1",          "attributes",         clsInvoke,      12,     0                  },
         {      12,     Trait::TYPE_GET,        "cXmlNode1",          "ownerDocument",      clsInvoke,      13,     0                  },
         {      13,     Trait::TYPE_FUN,        "cXmlNode1",          "insertBefore",       clsInvoke,      14,     0                  },
         {      14,     Trait::TYPE_FUN,        "cXmlNode1",          "replaceChild",       clsInvoke,      15,     0                  },
         {      15,     Trait::TYPE_FUN,        "cXmlNode1",          "removeChild",        clsInvoke,      16,     0                  },
         {      16,     Trait::TYPE_FUN,        "cXmlNode1",          "appendChild",        clsInvoke,      17,     0                  },
         {      17,     Trait::TYPE_GET,        "cXmlNode1",          "hasChildNodes",      clsInvoke,      18,     0                  },
         {      18,     Trait::TYPE_FUN,        "cXmlNode1",          "cloneNode",          clsInvoke,      19,     0                  },
         {      0,      Trait::TYPE_END,        "cXmlNode1",          0,                    0,              0,      0                  },
      };

      return TRAITS;
}

Trait* cXmlNode1::extTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cXmlNode1",          0,                    0,              0,      0                  },
         {      0,      Trait::TYPE_END,        "cXmlNode1",          0,                    0,              0,      0                  },
      };

      return TRAITS;
}

siEx cXmlNode1::clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cXmlNode1* pthis1 = (cXmlNode1*) pthis;

      switch(index) {
         case 0:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->replaceNode(ctx,siXmlNode (argv[0].toScr())));
            break;
         case 1:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->xml();
            break;
         case 2:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->nodeName();
            break;
         case 3:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->nodeValue();
            break;
         case 4:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->setNodeValue(argv[0].toStr());
            break;
         case 5:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->nodeType();
            break;
         case 6:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->parentNode(ctx));
            break;
         case 7:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNodeList(pthis1->childNodes());
            break;
         case 8:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->firstChild(ctx));
            break;
         case 9:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->lastChild(ctx));
            break;
         case 10:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->previousSibling(ctx));
            break;
         case 11:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->nextSibling(ctx));
            break;
         case 12:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNamedNodeMap(pthis1->attributes());
            break;
         case 13:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlDocument(pthis1->ownerDocument(ctx));
            break;
         case 14:
            if (argc != 2)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->insertBefore(siXmlNode (argv[0].toScr()),siXmlNode (argv[1].toScr())));
            break;
         case 15:
            if (argc != 2)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->replaceChild(siXmlNode (argv[0].toScr()),siXmlNode (argv[1].toScr())));
            break;
         case 16:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->removeChild(siXmlNode (argv[0].toScr())));
            break;
         case 17:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->appendChild(siXmlNode (argv[0].toScr())));
            break;
         case 18:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->hasChildNodes();
            break;
         case 19:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlNode(pthis1->cloneNode(ctx,argv[0].toBool()));
            break;
      }
      return ex;
}

siEx cXmlNode1::extInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      return ex;
}

}
#endif
#pragma warning(default : 4100)
#pragma warning(default : 4189)
