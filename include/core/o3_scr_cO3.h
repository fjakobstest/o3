#ifdef O3_WITH_GLUE
#pragma warning( disable : 4100)
#pragma warning( disable : 4189)
namespace o3 {


Trait* cO3::select()
{
   return clsTraits();
}

Trait* cO3::clsTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cO3",                0,                    0,              0,      cScr::clsTraits()  },
         {      0,      Trait::TYPE_GET,        "cO3",                "args",               clsInvoke,      0,      0                  },
         {      1,      Trait::TYPE_GET,        "cO3",                "envs",               clsInvoke,      1,      0                  },
         {      2,      Trait::TYPE_FUN,        "cO3",                "loadModule",         clsInvoke,      2,      0                  },
         {      3,      Trait::TYPE_FUN,        "cO3",                "wait",               clsInvoke,      3,      0                  },
         {      4,      Trait::TYPE_FUN,        "cO3",                "exit",               clsInvoke,      4,      0                  },
         {      5,      Trait::TYPE_GET,        "cO3",                "versionInfo",        clsInvoke,      5,      0                  },
         {      0,      Trait::TYPE_END,        "cO3",                0,                    0,              0,      0                  },
      };

      return TRAITS;
}

Trait* cO3::extTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cO3",                0,                    0,              0,      0                  },
         {      0,      Trait::TYPE_END,        "cO3",                0,                    0,              0,      0                  },
      };

      return TRAITS;
}

siEx cO3::clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cO3* pthis1 = (cO3*) pthis;

      switch(index) {
         case 0:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( args )");
            *rval = o3_new(tScrVec<Str>)(pthis1->args());
            break;
         case 1:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( envs )");
            *rval = o3_new(tScrVec<Str>)(pthis1->envs());
            break;
         case 2:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count. ( loadModule )");
            *rval = pthis1->loadModule(ctx,argv[0].toStr());
            break;
         case 3:
            if (argc > 1)
               return o3_new(cEx)("Invalid argument count. ( wait )");
            pthis1->wait(ctx,argc > 0 ? argv[0].toInt32() : -1);
            break;
         case 4:
            if (argc > 1)
               return o3_new(cEx)("Invalid argument count. ( exit )");
            pthis1->exit(argc > 0 ? argv[0].toInt32() : 0);
            break;
         case 5:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count. ( versionInfo )");
            *rval = pthis1->versionInfo();
            break;
      }
      return ex;
}

siEx cO3::extInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      return ex;
}

}
#endif
#pragma warning(default : 4100)
#pragma warning(default : 4189)
