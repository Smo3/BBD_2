function [h]=rir(fs, mic, n, r, rm, src)

%RIR   Room Impulse Response (kambario impulsinis atsakas).

%   [h] = RIR(FS, MIC, N, R, RM, SRC) Paprastas kambario impusinio atsako

%   skaiciavimas

%

%      FS =  diskretizacijos daznis.

%      MIC = mikrofono koordinates isreikstos paprastu vektoriu x,y,z

%      N =   atspindziu skaicius (2*N+1)^3.

%      R =   kambario sienu atspindzio koeficientas -1<R<1.

%      RM =  kambario dydis isreikstas paprastu vektoriu.  

%      SRC = Garso saltinio koordinates isreikstos x,y,z vektoriumi.

%

%   DEMESIO:

%   1) Visi atstumai matuojami metrais.



nn=[-n:1:n];                          % sekos indeksai
rms=nn+0.5-0.5*(-1).^nn;              % dalis 4.4,4.5,ir 4.6 formules
srcs=(-1).^(nn);                      % dalis 4.4,4.5,ir 4.6 formules

xi=[srcs*src(1)+rms*rm(1)-mic(1)];    % pagal 4.4 formule 
yj=[srcs*src(2)+rms*rm(2)-mic(2)];    % pagal 4.5 formule 
zk=[srcs*src(3)+rms*rm(3)-mic(3)];    % pagal 4.6 formule 


[i,j,k]=meshgrid(xi,yj,zk);           % vektoriu pertvarkymas i 3D matricas
d=sqrt(i.^2+j.^2+k.^2);               % pagal 4.7 formule
time=round(fs*d/343)+1;               % pagal 4.8 formule


[e,f,g]=meshgrid(nn, nn, nn);         % vektoriu pertvarkymas i 3D matricas
c=r.^(abs(e)+abs(f)+abs(g));          % Pagal 4.11 formule
e=c./d;                               % Pagal 4.12 formule


h=full(sparse(time(:),1,e(:)));       % Pagal 4.14 formule
