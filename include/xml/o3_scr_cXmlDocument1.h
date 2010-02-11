#ifdef O3_WITH_GLUE
#pragma warning( disable : 4100)
#pragma warning( disable : 4189)
namespace o3 {


Trait* cXmlDocument1::select()
{
   return clsTraits();
}

Trait* cXmlDocument1::clsTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cXmlDocument1",      0,                    0,              0,      cXmlNode1::clsTraits()  },
         {      0,      Trait::TYPE_GET,        "cXmlDocument1",      "documentElement",    clsInvoke,      0,      0                  },
         {      1,      Trait::TYPE_FUN,        "cXmlDocument1",      "createElement",      clsInvoke,      1,      0                  },
         {      2,      Trait::TYPE_FUN,        "cXmlDocument1",      "createTextNode",     clsInvoke,      2,      0                  },
         {      3,      Trait::TYPE_FUN,        "cXmlDocument1",      "createComment",      clsInvoke,      3,      0                  },
         {      4,      Trait::TYPE_FUN,        "cXmlDocument1",      "createCDATASection", clsInvoke,      4,      0                  },
         {      5,      Trait::TYPE_FUN,        "cXmlDocument1",      "createAttribute",    clsInvoke,      5,      0                  },
         {      0,      Trait::TYPE_END,        "cXmlDocument1",      0,                    0,              0,      0                  },
      };

      return TRAITS;
}

Trait* cXmlDocument1::extTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cXmlDocument1",      0,                    0,              0,      0                  },
         {      0,      Trait::TYPE_END,        "cXmlDocument1",      0,                    0,              0,      0                  },
      };

      return TRAITS;
}

siEx cXmlDocument1::clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cXmlDocument1* pthis1 = (cXmlDocument1*) pthis;

      switch(index) {
         case 0:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlElement(pthis1->documentElement(ctx));
            break;
         case 1:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlElement(pthis1->createElement(ctx,argv[0].toStr()));
            break;
         case 2:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlText(pthis1->createTextNode(ctx,argv[0].toStr()));
            break;
         case 3:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlComment(pthis1->createComment(ctx,argv[0].toStr()));
            break;
         case 4:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlCDATASection(pthis1->createCDATASection(ctx,argv[0].toStr()));
            break;
         case 5:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siXmlAttr(pthis1->createAttribute(ctx,argv[0].toStr()));
            break;
      }
      return ex;
}

siEx cXmlDocument1::extInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      return ex;
}

}
#endif
#pragma warning(default : 4100)
#pragma warning(default : 4189)
