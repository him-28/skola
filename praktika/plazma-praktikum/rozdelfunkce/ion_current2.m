function ion_current2(vst,up,vyst)
%ion_current(vst,up,vyst)
%Odecita iontovy proud od sondove charakteristiky. 
%Upravovana VA charakteristika sondy je v souboru vst (1. sloupec: napeti, 2. sloupec: proud), 
%vysledek ulozi do souboru vyst. 
%Parametr up je hodnota potencialu plazmatu. 
%(Nazvy souboru je treba umistit mezi apostrofy.)
%
%Programek na zacatku nakresli zlogaritmovanou charakteristiku sondy nad plovoucim potencialem 
% (s potencialem plazmatu oznacenym cervenym krouzkem) a zepta se na oblast, ze ktere ma odhadnout vlastnosti EEDF. 
% Zde je potreba zadat hranice (dve hodnoty napeti, pocinaje mensim napetim, ve tvaru [x1 x2]) oblasti 
% pod potencialem plazmatu, kde VA charakteristika neni prilis ovlivnena ionty a je priblizne linearni. 
%
%V dalsim kroku program nakresli charakteristiku pod plovoucim potencialem v takovych souradnicich, 
% aby iontovy proud vykazoval linearni zavislost. Na tomto grafu lze rozlisit dve oblasti: 
% 1) Oblast s malymi hodnotami nezavisle promenne odpovida casti VA charakteristiky, ktera je blizko plovoucimu potencialu. 
%    V teto oblasti na sondu dopadaji i rychle elektrony a krivka proto neni linearni. 
% 2) Oblast s velkymi hodnotami nezavisle promenne, kde je kreslena krivka linearni, odpovida ciste iontovemu proudu. 
% Program se vypta na hranice linearni oblasti (druha oblast). V teto oblasti spocita vlastnosti iontoveho proudu. 
%
%Na zaver programek extrapoluje iontovy proud az po potencial plazmatu, vypise parametry iontoveho proudu (Iinul, kapa),
% odecte iontovy proud od VA charakteristiky sondy a vysledek ulozi. 
%Vysledek nakresli do dvou grafu, kde srovna puvodni (zelena krivka) a upravenou (modra krivka) VA charakteristiku sondy. 
% V prvnim grafu je na ose y proud, v druhem grafu jeho logaritmus. 
q=1.6021e-19; kb=1.380662e-23;
A=load(vst); 
n=length(A(:,1)); 
if A(1,2)>=0
 error('Charakteristika zacina kladnym proudem - neni mozne vyhodnotit iontovy proud!.')
end
pdlo=1;
while A(pdlo,2)<0,
 pdlo=pdlo+1;
end 
porup=1; 
while A(porup,1)<up,
 porup=porup+1;
end
Iup=A(porup,2);
pdlo2=n;
while A(pdlo2,2)>0,
 pdlo2=pdlo2-1;
end
figure; plot(A(pdlo2+1:n,1),log(A(pdlo2+1:n,2)),'b',up,log(Iup),'ro'); grid; hold on;
xlabel('U [V]'); ylabel('ln(I)'); title('Vyber linearni oblast pod potencialem plazmatu');
mez=input('Zadej hranice pro prolozeni primky ');
if length(mez)~=2
 disp('Jsou potreba 2 mezni hodnoty!');
 mez=input('Zadej hranice pro prolozeni primky ');
elseif mez(2)<=mez(1)
 disp('Druha hodnota musi byt vetsi nez prvni!');
 mez=input('Zadej hranice pro prolozeni primky ');
end
j=1;
if mez(1)>A(1,1)
 while A(j,1)<mez(1),
  j=j+1; 
 end
end
mez(1)=j; 
if mez(2)>A(n,1)
 mez(2)=n; 
else
 while mez(2)>A(j,1), 
  j=j+1; 
 end
 mez(2)=j; 
end
iml=[log(A(pdlo2+6,2)) log(max(A(:,2)))];
plot([A(mez(1),1) A(mez(1),1)],iml,'m');
plot([A(mez(2),1) A(mez(2),1)],iml,'m');
nap=A(mez(1):mez(2),1);
pr=polyfit(nap,log(A(mez(1):mez(2),2)),1); 
plot(nap,polyval(pr,nap),'r'); 
Te0=q/(kb*pr(1)); Em0=3/(2*pr(1));
uio=up-A(1:pdlo-1,1); 
uio=log(1+uio*q/(kb*Te0));
iio=log(-A(1:pdlo-1,2));
figure; plot(uio,iio,'b'); grid; 
title('Vyber linearni oblast odpovidajici ciste iontovemu proudu'); 
mezi=input('Zadej mezni hodnoty pro vyhodnoceni iontoveho proudu ');
if length(mezi)~=2
 disp('Jsou potreba 2 mezni hodnoty!');
 mezi=input('Zadej mezni hodnoty pro vyhodnoceni iontoveho proudu ');
elseif mezi(2)<=mezi(1)
 disp('Druha hodnota musi byt vetsi nez prvni!');
 mezi=input('Zadej mezni hodnoty pro vyhodnoceni iontoveho proudu ');
end
j=1;
if mezi(2)<uio(1)
 while uio(j)>mezi(2),
  j=j+1; 
 end
end
mezi(2)=j;
if mezi(1)<=uio(pdlo-1)
 mezi(1)=pdlo-1; 
else
 while mezi(1)<uio(j), 
  j=j+1; 
 end
 mezi(1)=j;
end
mezi=[mezi(2) mezi(1)];
hold on; 
plot([uio(mezi(1)) uio(mezi(1))],[min(iio) max(iio)],'m');
plot([uio(mezi(2)) uio(mezi(2))],[min(iio) max(iio)],'m');
iopr=polyfit(uio(mezi(1):mezi(2)),iio(mezi(1):mezi(2)),1);
plot(uio(mezi(1):mezi(2)),polyval(iopr,uio(mezi(1):mezi(2))),'r');
Iinul=exp(iopr(2))
kapa=iopr(1)
Teplota=Te0

%Odecteni iontoveho proudu: 
Ii=Iinul*(1+q*(up-A(1:porup-1,1))/(kb*Te0)).^kapa;
%I2=[A(1:porup-1,2)+Ii; A((porup):length(A(:,1)),2)];
I2=[A(1:porup-1,2)+Ii; A((porup):length(A(:,1)),2)+Iinul];%odečítá na celé ose kvůli druhé derivaci
B=[A(:,1) I2]; %Vektor s korigovanym proudem
figure; plot(A(:,1),A(:,2),'g',B(:,1),B(:,2),'b'); grid; %Vygrafeni puvodni (zelene) a upravene (modre) charakteristiky. 
xlabel('U [V]'), ylabel('I  [A]'); title('Merena VA charakteristika sondy (zelene) a jeji elektronova cast (modre)');
figure; plot(A(:,1),log(A(:,2)),'g',B(:,1),log(B(:,2)),'b'); grid; %Vygrafeni zlogaritmovanych charakteristik. 
xlabel('U [V]'), ylabel('ln(I)'); title('Logaritmus merene VA charakteristiky sondy (zelene) a jeji elektronove casti (modre)');
save(vyst,'B','-ascii');
