Testing math
============



.. uml::


  @startuml
  start
  :<math>(y;r)</math> at <math>t=hk</math>;
  :<math>y ← P(h) y + x^{k+1}</math>;
  if (<math>r > 0</math>) then (yes)
    :<math>r ← r - 1</math>;
    :<math>y_m ← 0</math>;
  else (no);
    if (<math>y_m> theta</math>) then (yes)
      :<math>r ← tau_r(h)</math>;
      :<math>y_m ← 0</math>;
    else (no);
    endif
  endif
  :<math> (y;r)</math> at <math>t=h(k+1)</math>;
  :<latex>\int_0^1 f(x) dx</latex>;
  stop
  @enduml
