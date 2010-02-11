#ifdef O3_WITH_GLUE
#pragma warning( disable : 4100)
#pragma warning( disable : 4189)
namespace o3 {


Trait* cProcess1Base::select()
{
   return clsTraits();
}

Trait* cProcess1Base::clsTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cProcess1Base",      0,                    0,              0,      cScr::clsTraits()  },
         {      0,      Trait::TYPE_GET,        "cProcess1Base",      "stdIn",              clsInvoke,      0,      0                  },
         {      0,      Trait::TYPE_SET,        "cProcess1Base",      "stdIn",              clsInvoke,      1,      0                  },
         {      1,      Trait::TYPE_GET,        "cProcess1Base",      "stdOut",             clsInvoke,      2,      0                  },
         {      1,      Trait::TYPE_SET,        "cProcess1Base",      "stdOut",             clsInvoke,      3,      0                  },
         {      2,      Trait::TYPE_GET,        "cProcess1Base",      "stdErr",             clsInvoke,      4,      0                  },
         {      2,      Trait::TYPE_SET,        "cProcess1Base",      "stdErr",             clsInvoke,      5,      0                  },
         {      3,      Trait::TYPE_FUN,        "cProcess1Base",      "exec",               clsInvoke,      6,      0                  },
         {      0,      Trait::TYPE_END,        "cProcess1Base",      0,                    0,              0,      0                  },
      };

      return TRAITS;
}

Trait* cProcess1Base::extTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cProcess1Base",      0,                    0,              0,      0                  },
         {      0,      Trait::TYPE_END,        "cProcess1Base",      0,                    0,              0,      0                  },
      };

      return TRAITS;
}

siEx cProcess1Base::clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cProcess1Base* pthis1 = (cProcess1Base*) pthis;

      switch(index) {
         case 0:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siStream(pthis1->stdIn());
            break;
         case 1:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siStream(pthis1->setStdIn(siStream (argv[0].toScr())));
            break;
         case 2:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siStream(pthis1->stdOut());
            break;
         case 3:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siStream(pthis1->setStdOut(siStream (argv[0].toScr())));
            break;
         case 4:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siStream(pthis1->stdErr());
            break;
         case 5:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siStream(pthis1->setStdErr(siStream (argv[0].toScr())));
            break;
         case 6:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->exec(argv[0].toStr());
            break;
      }
      return ex;
}

siEx cProcess1Base::extInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      return ex;
}

}
#endif
#pragma warning(default : 4100)
#pragma warning(default : 4189)
