function derivace(vst,vyh,vyst)
%derivace(vst,vyh,vyst)
%Pocita prvni a druhou derivaci dat nactenych ze souboru vst (prvni sloupec nezavisle promenna, druhy sloupec zavisle promenna). 
%Derivaci pocita pomoci prokladani paraboly 2*vyh+1 body. (vyh je prirozene cislo). 
%Vysledek uklada do souboru vyst (1. sloupec: nezavisle promenna, 2. sloupec: prvni derivace, 3. sloupec: druha derivace). 
%(Nazvy souboru je treba umistit mezi apostrofy.)
%
%V tele funkce jsou tri volitelne parametry: 
%Parametr R urcuje, jakym zpusobem se bude druha derivace pocitat. 
% Je-li R=0, dava se pri vypoctu derivaci vsem 2*vyh+1 bodu stejnou vahu, 
% pri R=1 dava vetsi vahu bodum v centru oblasti, ze ktere se prave derivace pocitaji. 
% (Pro vyhodnocovani sondovych mereni doporucuji R=1.) 
%
%Parametr orezaut ridi, zda se pred vypoctem derivaci odstrani zacatek mereni (vhodne u mereni sondou od Hiden). 
% Je-li prvni hodnota vektoru orezaut 1, pak program nakresli mereni a zepta se, po jakou hodnotu nezavisle promenne (napeti) ma mereni odriznout. 
% Je-li prvni hodnota vektoru orezaut 2, pak program automaticky odrizne mereni az po hodnotu zadanou jako druhy clen vektoru orezaut. 
%
%Parametr G pouze ovlivnuje formu, jakou jsou derivace zobrazeny v grafu. 
% Pri G=1 jsou upravena meritka pro zobrazeni derivaci tak, aby byl graf prehledny (doporucuji pro vyhodnocovani sondovych mereni). 
% Pri G=2 jsou derivace zobrazeny ve spravnem meritku. 

R=1; 
orezaut=[1 -20]; 
G=1;

A=load(vst);
n=length(A(:,1));

%Odriznuti zacatku mereni:
if orezaut(1)==1
 plot(A(:,1),A(:,2),'b'); grid;
 orez=input('Zadej napeti, po ktere se ma VA charakteristika odriznout  ');
elseif orezaut(1)==2 
 orez=orezaut(2);
end
if orezaut(1) == 1 | orezaut(1) ==2
 if orez>max(A(:,1))
  error('Odstranena cela VA charakteristika.');
 end
 if orez>A(1,1)
  j=1;
  while A(j,1)<=orez,
   j=j+1;
  end
  j=j-1;
  A=A(j:n,:);
 end
 n=length(A(:,1));
end

%Spocitani matice derivaci D (prvni sloupec - napeti, druhy sloupec - 1. derivace, 2. sloupec - druha derivace).
vyh=round(vyh);
if vyh<1
 error('Druhou derivaci je mozne pocitat z minimalne tri bodu (parametr vyh musi byt >= 1)!');
end
if n<2*vyh+1
 error('Charakteristika nema dostatek bodu (prilis velky parametr vyh)!');
end

D=[];
if R==0
 for j=1:n-2*vyh,
  V=A(j:j+2*vyh,:);
  usour=mean(V(:,1));
  pom=polyfit(V(:,1)-usour,V(:,2),2);
  D=[D; usour pom(2) 2*pom(1)];
 end
elseif R==1
 for i=1:n-2*vyh,
  aa=[]; bb=[];
  for j=0:vyh,
   aa=[aa (A(vyh+i-j:vyh+i+j,1))'];
   bb=[bb (A(vyh+i-j:vyh+i+j,2))'];
  end
  usour=mean(aa);
  pom=polyfit(aa-usour,bb,2);
  D=[D; usour pom(2) 2*pom(1)];
 end
else
 error('R musi mit hodnotu 0 nebo 1.');
end

%Vygrafeni: 
im=max(A(:,2)); dm=max(D(:,3)); pm=max(D(:,2));
figure; 
plot([A(1,1) A(n,1)],[0 0],'k'); hold on; xlabel('U [V]');
plot(A(:,1),A(:,2),'b'); 
if G==1
 plot(D(:,1),D(:,3)*im/dm,'g',D(:,1),D(:,2)*im/pm,'c');
 ylabel('Aby byl graf prehledny, maji derivace v grafu zmenene meritko.')
elseif G==2
 plot(D(:,1),D(:,3),'g',D(:,1),D(:,2),'c');
end
grid; title('Vstupni data (modre), prvni (tyrkysove) a druha (zelene) derivace.');

%Ulozeni: 
save(vyst,'D','-ascii');