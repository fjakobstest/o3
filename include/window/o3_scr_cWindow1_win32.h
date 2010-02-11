#ifdef O3_WITH_GLUE
#pragma warning( disable : 4100)
#pragma warning( disable : 4189)
namespace o3 {


Trait* cWindow1::select()
{
   return clsTraits();
}

Trait* cWindow1::clsTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cWindow1",           0,                    0,              0,      cWindow1Base::clsTraits()  },
         {      0,      Trait::TYPE_FUN,        "cWindow1",           "createWindow",       clsInvoke,      0,      0                  },
         {      1,      Trait::TYPE_GET,        "cWindow1",           "clientX",            clsInvoke,      1,      0                  },
         {      2,      Trait::TYPE_GET,        "cWindow1",           "clientY",            clsInvoke,      2,      0                  },
         {      3,      Trait::TYPE_FUN,        "cWindow1",           "minimize",           clsInvoke,      3,      0                  },
         {      4,      Trait::TYPE_FUN,        "cWindow1",           "maximize",           clsInvoke,      4,      0                  },
         {      5,      Trait::TYPE_FUN,        "cWindow1",           "restore",            clsInvoke,      5,      0                  },
         {      6,      Trait::TYPE_FUN,        "cWindow1",           "close",              clsInvoke,      6,      0                  },
         {      7,      Trait::TYPE_SET,        "cWindow1",           "visible",            clsInvoke,      7,      0                  },
         {      8,      Trait::TYPE_GET,        "cWindow1",           "showButtons",        clsInvoke,      8,      0                  },
         {      8,      Trait::TYPE_SET,        "cWindow1",           "showButtons",        clsInvoke,      9,      0                  },
         {      9,      Trait::TYPE_GET,        "cWindow1",           "caption",            clsInvoke,      10,     0                  },
         {      9,      Trait::TYPE_SET,        "cWindow1",           "caption",            clsInvoke,      11,     0                  },
         {      10,     Trait::TYPE_SET,        "cWindow1",           "icon",               clsInvoke,      12,     0                  },
         {      11,     Trait::TYPE_FUN,        "cWindow1",           "open",               clsInvoke,      13,     0                  },
         {      12,     Trait::TYPE_FUN,        "cWindow1",           "useIcon",            clsInvoke,      14,     0                  },
         {      13,     Trait::TYPE_FUN,        "cWindow1",           "focus",              clsInvoke,      15,     0                  },
         {      14,     Trait::TYPE_FUN,        "cWindow1",           "destroy",            clsInvoke,      16,     0                  },
         {      15,     Trait::TYPE_SET,        "cWindow1",           "onclose",            clsInvoke,      17,     0                  },
         {      16,     Trait::TYPE_SET,        "cWindow1",           "onend",              clsInvoke,      18,     0                  },
         {      0,      Trait::TYPE_END,        "cWindow1",           0,                    0,              0,      0                  },
      };

      return TRAITS;
}

Trait* cWindow1::extTraits()
{
      static Trait TRAITS[] = {
         {      0,      Trait::TYPE_BEGIN,      "cWindow1",           0,                    0,              0,      0                  },
         {      0,      Trait::TYPE_GET,        "cO3",                "window",             extInvoke,      0,      0                  },
         {      1,      Trait::TYPE_FUN,        "cO3",                "createWindow",       extInvoke,      1,      0                  },
         {      2,      Trait::TYPE_FUN,        "cO3",                "sendKeyEvent",       extInvoke,      2,      0                  },
         {      3,      Trait::TYPE_FUN,        "cO3",                "mouseTo",            extInvoke,      3,      0                  },
         {      4,      Trait::TYPE_FUN,        "cO3",                "mouseLeftClick",     extInvoke,      4,      0                  },
         {      5,      Trait::TYPE_FUN,        "cO3",                "mouseRightClick",    extInvoke,      5,      0                  },
         {      6,      Trait::TYPE_FUN,        "cO3",                "mouseLeftDown",      extInvoke,      6,      0                  },
         {      7,      Trait::TYPE_FUN,        "cO3",                "mouseLeftUp",        extInvoke,      7,      0                  },
         {      8,      Trait::TYPE_FUN,        "cO3",                "mouseRightDown",     extInvoke,      8,      0                  },
         {      9,      Trait::TYPE_FUN,        "cO3",                "mouseRightUp",       extInvoke,      9,      0                  },
         {      10,     Trait::TYPE_FUN,        "cO3",                "mouseWheel",         extInvoke,      10,     0                  },
         {      11,     Trait::TYPE_FUN,        "cO3",                "alertBox",           extInvoke,      11,     0                  },
         {      0,      Trait::TYPE_END,        "cWindow1",           0,                    0,              0,      0                  },
      };

      return TRAITS;
}

siEx cWindow1::clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cWindow1* pthis1 = (cWindow1*) pthis;

      switch(index) {
         case 0:
            if (argc < 5 && argc > 6)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siWindow(pthis1->createWindow(argv[0].toStr(),argv[1].toInt32(),argv[2].toInt32(),argv[3].toInt32(),argv[4].toInt32(),argc > 5 ? argv[5].toInt32() : 0));
            break;
         case 1:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->clientX();
            break;
         case 2:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->clientY();
            break;
         case 3:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->minimize();
            break;
         case 4:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->maximize();
            break;
         case 5:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->restore();
            break;
         case 6:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->close();
            break;
         case 7:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->setVisible(argv[0].toBool());
            break;
         case 8:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->showButtons();
            break;
         case 9:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->setShowButtons(argv[0].toBool());
            break;
         case 10:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->caption();
            break;
         case 11:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->setCaption(argv[0].toStr());
            break;
         case 12:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->setIcon(argv[0].toStr());
            break;
         case 13:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->open();
            break;
         case 14:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->useIcon(Buf(siBuf(argv[0].toScr())));
            break;
         case 15:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->focus();
            break;
         case 16:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->destroy();
            break;
         case 17:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->setOnclose(ctx,argv[0].toScr());
            break;
         case 18:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->setOnend(ctx,argv[0].toScr());
            break;
      }
      return ex;
}

siEx cWindow1::extInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
           const Var* argv, Var* rval)
{
      siEx ex;
      cWindow1* pthis1 = (cWindow1*) pthis;

      switch(index) {
         case 0:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siWindow(pthis1->window(ctx));
            break;
         case 1:
            if (argc < 6 && argc > 7)
               return o3_new(cEx)("Invalid argument count.");
            *rval = siWindow(pthis1->createWindow(siUnk (argv[0].toScr()),argv[1].toStr(),argv[2].toInt32(),argv[3].toInt32(),argv[4].toInt32(),argv[5].toInt32(),argc > 6 ? argv[6].toInt32() : 0));
            break;
         case 2:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->sendKeyEvent(argv[0].toStr());
            break;
         case 3:
            if (argc < 2 && argc > 3)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->mouseTo(argv[0].toInt32(),argv[1].toInt32(),siWindow (argc > 2 ? argv[2].toScr() : 0));
            break;
         case 4:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->mouseLeftClick();
            break;
         case 5:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->mouseRightClick();
            break;
         case 6:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->mouseLeftDown();
            break;
         case 7:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->mouseLeftUp();
            break;
         case 8:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->mouseRightDown();
            break;
         case 9:
            if (argc != 0)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->mouseRightUp();
            break;
         case 10:
            if (argc != 1)
               return o3_new(cEx)("Invalid argument count.");
            pthis1->mouseWheel(argv[0].toInt32());
            break;
         case 11:
            if (argc < 2 && argc > 3)
               return o3_new(cEx)("Invalid argument count.");
            *rval = pthis1->alertBox(argv[0].toStr(),argv[1].toStr(),argc > 2 ? argv[2].toStr() : 0,&ex);
            break;
      }
      return ex;
}

}
#endif
#pragma warning(default : 4100)
#pragma warning(default : 4189)
