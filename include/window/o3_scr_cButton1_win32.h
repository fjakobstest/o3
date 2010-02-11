#ifdef O3_WITH_GLUE
#pragma warning( disable : 4100)
#pragma warning( disable : 4189)
namespace o3 {


Trait* cButton1::select()
{
   return clsTraits();
}

Trait* cButton1::clsTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cButton1",           0,                    0,              0,      cWindow1::clsTraits()  },
         {      0,      Trait::TYPE_SET,        "cButton1",           "onclick",            clsInvoke,      0,      0                  },
         {      0,      Trait::TYPE_END,        "cButton1",           0,                    0,              0,      0                  },
      };

      return TRAITS;
}

Trait* cButton1::extTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cButton1",           0,                    0,              0,      0                  },
         {      0,      Trait::TYPE_FUN,        "cWindow1",           "createButton",       extInvoke,      0,      0                  },
         {      1,      Trait::TYPE_FUN,        "cWindow1",           "createRButton",      extInvoke,      1,      0                  },
         {      0,      Trait::TYPE_END,        "cButton1",           0,                    0,              0,      0                  },
      };

      return TRAITS;
}

siEx cButton1::clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cButton1* pthis1 = (cButton1*) pthis;

      switch(index) {
         case 0:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->setOnclick(ctx,argv[0].toScr());
            break;
      }
      return ex;
}

siEx cButton1::extInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cButton1* pthis1 = (cButton1*) pthis;

      switch(index) {
         case 0:
            if (argc < 6 && argc > 8)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siWindow(pthis1->createButton(siUnk (argv[0].toScr()),argv[1].toStr(),argv[2].toInt32(),argv[3].toInt32(),argv[4].toInt32(),argv[5].toInt32(),argc > 6 ? argv[6].toInt32() : 16,argc > 7 ? argv[7].toInt32() : 0));
            break;
         case 1:
            if (argc < 6 && argc > 9)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siWindow(pthis1->createRButton(siUnk (argv[0].toScr()),argv[1].toStr(),argv[2].toInt32(),argv[3].toInt32(),argv[4].toInt32(),argv[5].toInt32(),argc > 6 ? argv[6].toInt32() : 16,argc > 7 ? argv[7].toInt32() : 0,argc > 8 ? argv[8].toInt32() : 0));
            break;
      }
      return ex;
}

}
#endif
#pragma warning(default : 4100)
#pragma warning(default : 4189)
