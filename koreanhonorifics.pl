/* Korean Honorofics and Politeness */
:- ['properties.pl'].
:- ['entailment.pl'].

/* Honorific - The title for people implementation */
/* For -nim titles. */
person([h,a,r,a,b,e,o,j,i], grandfather).
person([h,a,l,m,e,o,n,i], grandmother).
person([a,b,e,o,j,i], father).
person([e,o,m,e,o,n,i], mother).
person([h,y,e,o,n,g], brother).
person([n,u,n,a], malesoldersister).
person([o,p,p,a], femalesolderbrother).
person([e,o,n,n,i], femalesoldersister).
person([a,d,e,u,l], son).
person([t,t,a,l], daughter).
person([s,e,o,n,s,a,e,n,g], teacher).

/* Predicate for -nim degree of politeness is high */
person([N,I,M], [hsuffix, high], suffix):-
  phone(N), nas(N), alv(N),
  phone(I), not(bck(I)), tns(I),
  phone(M), nas(M), lab(M).
  
/* PROCESS 1 */
/* MAIN honorific predicate to make all of atoms honorific */
honorific(All):-
  underhonorific(All, [honorific, _]).

/* Affixation to the person to create honorific. Change all person's base noun form to honorific form */
/* nouns ending with -ji change -ji to -nim, **/
/* This predicate gets last two letters of each person's title and checks condition and adds suffix -nim */
underhonorific(X, [honorific, regular]):-
  person(Title, _),
  reverse(Title, RevTitle),
  [LastLett|Remain] = RevTitle,
  [SecLast|NoLastTwo] = Remain,
  reverse(NoLastTwo, Beginning),
  person(Nim, [_,high], suffix),
  [FirstOfSuffix|_] = Nim,
  homorganicity(SecLast, LastLett, FirstOfSuffix),
  append(Beginning, Nim, X).

/* nouns ending with -ng, -ul add -nim */
underhonorific(X, [honorific, regular]):-
  person(Title, _),   
  reverse(Title, RevTitle),
  [LastLett|Remain] = RevTitle,
  [SecLast|_] = Remain,
  homorganicity1(SecLast, LastLett),
  person(Nim, [_,high], suffix),
  append(Title, Nim, X).
  
/* special honorific that cannot add suffix -nim */
underhonorific([a,h,j,u,M,M,A], [honorific, special]):-
    phone(M), nas(M), lab(M),
    phone(A), not(mid(A)), bck(A), low(A).

underhonorific([a,h,j,u,S,S,I], [honorific, special]):-
    phone(S), sib(S), alv(S), not(voi(S)),
    phone(I), tns(I), not(bck(I)).
  
/* special case for ttal */
underhonorific(X, [honorific, special]):-
  person(Title, _),
  reverse(Title, RevTitle),
  [LastLett|Remain] = RevTitle,
  [SecLast|NoLastTwo] = Remain,
  homorganicity3(SecLast, LastLett),
  reverse(NoLastTwo, Beginning),
  append(Beginning, [a], Tta),
  person(Nim, [_,high], suffix),
  append(Tta, Nim, X).  
  
/* special case for oppa */
underhonorific(X, [honorific, special]):-
  person(Title, _),
  reverse(Title, RevTitle),
  [LastLett,SecLast|Remain] = RevTitle,
  homorganicity2(SecLast, LastLett),
  [_|O] = Remain,
  append(O,[r,a,b,e,o,n,i],X).
  
homorganicity(Y, Z, N):-
  pal(Y) => nas(N),
  not(cnt(Z)) => not(nas(N)),
  not(voi(Y)) => not(nas(N)),
  not(cns(Y)) => not(nas(N)).
  
/* check for ng, ul to append nim */
homorganicity1(Y,Z):-
  voi(Y) => cns(Z),
  not(voi(Y)) => cns(Z),
  not(tns(Y)) => not(cnt(Z)).
homorganicity2(Y,Z):-
  snt(Y) => not(cns(Z)),
  not(tns(Y)) <=> not(tns(Z)),
  lab(Y) <=> not(cns(Z)).
homorganicity3(Y,Z):-
  not(cns(Y)) <=> cns(Z),
  cns(Y) => cns(Z),
  not(alv(Y)) => alv(Z),
  not(tns(Y)) <=> cnt(Z).
  
/* Predicate for -ssi  degree of politeness is lower than -nim */
person([S,S,I], [hsuffix, lesshigh], suffix):-
  phone(S), sib(S), alv(S), not(voi(S)),
  phone(I), not(bck(I)), tns(I).
  
/* Predicate for -yah */
person([y,A,H], [hsuffix, low], suffix):-
  phone(A), not(mid(A)), bck(A), low(A),
  phone(H), not(voi(H)), not(ant(H)), cnt(H), not(nas(H)), not(lab(H)), not(pal(H)).
  
/* Predicate for -ah */
person([A,H], [hsuffix, low], suffix):-
  phone(A), not(mid(A)), bck(A), low(A),
  phone(H), not(voi(H)), not(ant(H)), cnt(H), not(nas(H)), not(lab(H)), not(pal(H)).
  
/* PROCESS 2 */
/* Implementation of allowed suffix to call another person */  
whattocall(Name1, Age1, Name2, Age2, Result):-
  ( Age1>Age2,
  person(Name1, Name2, Result, [informal])
    ; person(Name1, Name2, Result, [formal]) ).
  
/* -ah/-yah suffix appended to name */
person(_,Y,Z,[informal]):-
  last(Y, LastLett),
  person(Suffix, [hsuffix, low], suffix),
  [FirstOfSuff|_] = Suffix,
  cns(LastLett) <=> phone(FirstOfSuff),
  append(Y, Suffix, Z).

/* -ssi suffix appended to name */
person(_,Y,Z,[formal]):-
  last(Y, LastLett),
  person(Suffix, [hsuffix, lesshigh], suffix),
  [FirstOfSuff|_] = Suffix,
  append(Y, Suffix, Z).
  
/* Implementation for polite verb forms for formal speech */

/* Verb stems  */
verbstem([s,a], toeat). 
verbstem([j,a], tobuy). 
verbstem([g,a], togo). 
verbstem([d,u], toput). 
verbstem([o], tocome).   
verbstem([b,o], tosee).    
verbstem([c,h,i], tohit). 
verbstem([j,i], tolose). 
verbstem([m,a,s,i], todrink). 
verbstem([m,a,n,a], tomeet). 
verbstem([j,u], togive). 
verbstem([n,a,n,u], toshare). 
verbstem([t,a,e,u], toburn). 
verbstem([b,a,e,u], tolearn). 
verbstem([i,l,h,a,d,a], towork). 
verbstem([j,e,o,n,h,w,a,h,a,d,a], tomakeaphonecall).  
verbstem([u,n,j,e,o,n,h,a,d,a], todrive).  

/* MAIN predicate to get all of the polite forms of the verbs */
politeverb(All):-
  underpoliteverb(All, [verb,_]).

/* -yo suffix */
underpoliteverb([y,O], [suffix, yo]):-
    phone(O), not(cns(O)), bck(O), mid(O).
  
/* -haeyo suffix */
underpoliteverb([H,A,E,y,O], [suffix, haeyo]):-
    phone(H), not(voi(H)), not(ant(H)), cnt(H), not(nas(H)), not(lab(H)), not(pal(H)),
    phone(A), not(mid(A)), bck(A), low(A),
    phone(E), mid(E), not(ctr(E)), not(bck(E)),
    phone(O), not(cns(O)), bck(O), mid(O).
    
/* verb stems ending with -a is concatenated with -yo */
underpoliteverb(X, [verb, a]):-  
  verbstem(VStem, _),
  reverse(VStem, RVStem),
  [A,D|Remaining] = RVStem,
  check_a(A),
  not((phone(D), not(cnt(D)), alv(D), not(snt(D)), voi(D))),
  underpoliteverb(Suffix, [suffix,_]),
  [FirstSuffix | _] = Suffix,
  not(check_hada(FirstSuffix)),
  append(VStem, Suffix, X).

/* verb stems ending with -hada gets replaced with haeyo */
underpoliteverb(X, [verb, hada]):-
  verbstem(VStem, _),
  reverse(VStem, RVStem),
  [A,D,A,H|Remaining] = RVStem,
  check_hada(H),
  check_a(A),
  reverse(Remaining, Beginning),
  underpoliteverb(Suffix, [suffix,_]),
  [FirstSuff|_] = Suffix,
  not(check_hada(FirstSuff)),
  append(Beginning, [h,a,e], Beginning2),
  append(Beginning2, Suffix, X).

/* verb ending in -o will become -wa and appended with yo */
underpoliteverb(X, [verb, o]):-
  verbstem(VStem, _),
  reverse(VStem, RevStem),
  [O|B] = RevStem,
  mid(O), bck(O),
  underpoliteverb(YO, [suffix,_]),
  [Y|_] = YO,
  not(check_hada(Y)),
  append(B, [w,a], _WA),
  append(_WA, YO, X).
  
/* verb ending with -i will be replaced with -yeo and appended with yo */
underpoliteverb(X, [verb, i]):-
  verbstem(VStem, _),
  reverse(VStem, RevStem),
  [I|Rest] = RevStem,
  phone(I), tns(I), not(bck(I)),
  reverse(Rest, Beginning),
  append(Beginning, [y,e,o], Beginning2),
  underpoliteverb(YO, [suffix,_]),
  [Y|_] = YO,
  not(check_hada(Y)),
  append(Beginning2, YO, X).
 
/* verbs ending with -u gets replaced with -wo appended with -yo */
underpoliteverb(X, [verb, u]):-
  verbstem(VStem, _),
  reverse(VStem, RevStem),
  [U|Rest] = RevStem,
  phone(U), bck(U), tns(U),
  reverse(Rest, Beginning),
  append(Beginning, [w,o], Beginning2),
  underpoliteverb(YO, [suffix,_]),
  [Y|_] = YO,
  not(check_hada(Y)),
  append(Beginning2, YO, X).
  
/* Used several times to check if stems ended with an -a and -hada case */
/* Checks if a phone is the letter a */
check_a(A):-
      phone(A), not(mid(A)), bck(A), low(A).
      
/* Checks if the phone is the letter h */
check_hada(H):-
  phone(H), not(voi(H)), not(ant(H)), cnt(H), not(nas(H)), not(lab(H)), not(pal(H)).