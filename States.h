typedef enum
{
   tick_ev
  ,button_ev
} events;

char *rgEventTxt[]=
{
   "tick_ev"
  ,"button_ev"
};

typedef enum
{
   idle_st
  ,bfwait_st
  ,pdwait_st
  ,sandbfwait_st
}states;

char *rgStateTxt[]
{
   "idle_st"
  ,"bfwait_st"
  ,"pdwait_st"
  ,"sandbfwait_st"
};

#define TT StateTransitionType
//                  tick                           button
TT idle_std[]=      {{idle_st,0},                  {bfwait_st,&startbf}};
TT bfwait_std[]=    {{pdwait_st,&startpd},         {bfwait_st,0}};
TT pdwait_std[]=    {{sandbfwait_st,&startsandbf}, {pdwait_st,0}};
TT sandbfwait_std[]={{idle_st,&done},              {sandbfwait_st,0}};

StateTransitionType *transTable[]=
{
   idle_std
  ,bfwait_std
  ,pdwait_std
  ,sandbfwait_std
};

FSM fsm(transTable, rgStateTxt, rgEventTxt);
