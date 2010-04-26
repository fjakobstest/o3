#ifdef O3_WITH_GLUE
#pragma warning( disable : 4100)
#pragma warning( disable : 4189)
namespace o3 {


Trait* cDOM1::select()
{
   return clsTraits();
}

Trait* cDOM1::clsTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cDOM1",              0,                    0,              0,      cScr::clsTraits()  },
         {      0,      Trait::TYPE_GET,        "cDOM1",              "ondblclick",         clsInvoke,      0,      0                  },
         {      0,      Trait::TYPE_SET,        "cDOM1",              "ondblclick",         clsInvoke,      1,      0                  },
         {      1,      Trait::TYPE_GET,        "cDOM1",              "onclick",            clsInvoke,      2,      0                  },
         {      1,      Trait::TYPE_SET,        "cDOM1",              "onclick",            clsInvoke,      3,      0                  },
         {      2,      Trait::TYPE_GET,        "cDOM1",              "onmousedown",        clsInvoke,      4,      0                  },
         {      2,      Trait::TYPE_SET,        "cDOM1",              "onmousedown",        clsInvoke,      5,      0                  },
         {      3,      Trait::TYPE_GET,        "cDOM1",              "onmouseup",          clsInvoke,      6,      0                  },
         {      3,      Trait::TYPE_SET,        "cDOM1",              "onmouseup",          clsInvoke,      7,      0                  },
         {      4,      Trait::TYPE_GET,        "cDOM1",              "onmousemove",        clsInvoke,      8,      0                  },
         {      4,      Trait::TYPE_SET,        "cDOM1",              "onmousemove",        clsInvoke,      9,      0                  },
         {      5,      Trait::TYPE_GET,        "cDOM1",              "onmousewheel",       clsInvoke,      10,     0                  },
         {      5,      Trait::TYPE_SET,        "cDOM1",              "onmousewheel",       clsInvoke,      11,     0                  },
         {      6,      Trait::TYPE_GET,        "cDOM1",              "onkeyup",            clsInvoke,      12,     0                  },
         {      6,      Trait::TYPE_SET,        "cDOM1",              "onkeyup",            clsInvoke,      13,     0                  },
         {      7,      Trait::TYPE_GET,        "cDOM1",              "onkeydown",          clsInvoke,      14,     0                  },
         {      7,      Trait::TYPE_SET,        "cDOM1",              "onkeydown",          clsInvoke,      15,     0                  },
         {      8,      Trait::TYPE_GET,        "cDOM1",              "onkeypress",         clsInvoke,      16,     0                  },
         {      8,      Trait::TYPE_SET,        "cDOM1",              "onkeypress",         clsInvoke,      17,     0                  },
         {      0,      Trait::TYPE_END,        "cDOM1",              0,                    0,              0,      0                  },
      };

      return TRAITS;
}

Trait* cDOM1::extTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cDOM1",              0,                    0,              0,      0                  },
         {      0,      Trait::TYPE_GET,        "cO3",                "DOM",                extInvoke,      0,      0                  },
         {      0,      Trait::TYPE_END,        "cDOM1",              0,                    0,              0,      0                  },
      };

      return TRAITS;
}

siEx cDOM1::clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cDOM1* pthis1 = (cDOM1*) pthis;

      switch(index) {
         case 0:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( ondblclick )");
            *rval = pthis1->ondblclick();
            break;
         case 1:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOndblclick )");
            *rval = pthis1->setOndblclick(ctx,argv[0].toScr());
            break;
         case 2:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( onclick )");
            *rval = pthis1->onclick();
            break;
         case 3:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOnclick )");
            *rval = pthis1->setOnclick(ctx,argv[0].toScr());
            break;
         case 4:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( onmousedown )");
            *rval = pthis1->onmousedown();
            break;
         case 5:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOnmousedown )");
            *rval = pthis1->setOnmousedown(ctx,argv[0].toScr());
            break;
         case 6:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( onmouseup )");
            *rval = pthis1->onmouseup();
            break;
         case 7:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOnmouseup )");
            *rval = pthis1->setOnmouseup(ctx,argv[0].toScr());
            break;
         case 8:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( onmousemove )");
            *rval = pthis1->onmousemove();
            break;
         case 9:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOnmousemove )");
            *rval = pthis1->setOnmousemove(ctx,argv[0].toScr());
            break;
         case 10:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( onmousewheel )");
            *rval = pthis1->onmousewheel();
            break;
         case 11:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOnmousewheel )");
            *rval = pthis1->setOnmousewheel(ctx,argv[0].toScr());
            break;
         case 12:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( onkeyup )");
            *rval = pthis1->onkeyup();
            break;
         case 13:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOnkeyup )");
            *rval = pthis1->setOnkeyup(ctx,argv[0].toScr());
            break;
         case 14:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( onkeydown )");
            *rval = pthis1->onkeydown();
            break;
         case 15:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOnkeydown )");
            *rval = pthis1->setOnkeydown(ctx,argv[0].toScr());
            break;
         case 16:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( onkeypress )");
            *rval = pthis1->onkeypress();
            break;
         case 17:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( setOnkeypress )");
            *rval = pthis1->setOnkeypress(ctx,argv[0].toScr());
            break;
      }
      return ex;
}

siEx cDOM1::extInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cDOM1* pthis1 = (cDOM1*) pthis;

      switch(index) {
         case 0:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( DOM )");
            *rval = pthis1->DOM(ctx);
            break;
      }
      return ex;
}

}
#endif
#pragma warning(default : 4100)
#pragma warning(default : 4189)
