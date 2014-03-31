static void layoutscroll(const Arg *arg){ 
  int i=0; 
  while( !(selmon->lt[selmon->sellt] == &layouts[i]) ){
      i++;
  }
    setlayout(&(const Arg){.v = &layouts[(i + 1) % 3]});
} 

