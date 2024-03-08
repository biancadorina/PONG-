    -PONG-
	
		
	Programul implementeaza jocul pong. Programul are implementate 37 de functii. 
	
	Jocul incepe cu afisarea primului meniu care ofera posibilitatea jucatorului de a alege nivelul de dificultate: 
		- Easy(paletele au o dimensiune mai mare), prin apasarea tastei "E" 
		- Hard(dimensiunea paletelor se injumatateste),prin apasarea tastei "H".
		
	Aceste functionalitati au fost implementate prin intermediul functiilor: 
		- "level"(initializeaza matricea primului meniu), 
		- "print_menu"(afiseza meniul),
		- "choose"(face posibila alegerea nivelului de dificultate prin apasarea tastelor).
									
	Dupa ce jucatorul alege nivelul se afiseaza un al doilea meniu prin intermediul caruia alege numarul de jucatori: 
		- "multiplayer"(doi jucatori), prin apasarea tastei "2" 
		- "singleplayer"(o paleta va fi controlata de computer), prin apasarea tastei "1".
		
	De asemenea, cel de-al doilea meniu ofera posibilitatea de a iesi din joc "exit" prin apasarea tastei "3".
	
	Functii utilizate: 
	- "menu"(initializeaza matricea celui de-al doilea meniu), 
	- "print_menu"(afiseaza cel de-al doilea meniu), 
	- "choose2"(face posibila alegerea numarului de jucatori sau iesirea din joc), 
	- "go_to_game"(face posibila pornirea jocului). 
	
	Jocul este asemanator celui de ping-pong: prezinta doua palete si o minge, iar mingea nu trebuie sa treaca de cele doua bare orizontale, ricosand din cele verticale si din   palete. Bila este servita din palete, fiecare jucator avand cate doua serve consecutive. Jocul se termina cand unul dintre jucatori ajunge sa stranga 11 puncte, scorul fiind afisat in dreapta chenarului jocului. Paletele sunt controlate prin intermediul tastelor: cea de sus se misca la dreapta prin apasarea tastei "d" si la stanga cu tasta "a", iar
	cea de jos la dreapta cu sageata la dreapta si la stanga cu sageata in stanga.
	Atunci cand scorul ajunge la 11 puncte jocul se termina si este afisat castigatorul si ofera posibilitatea de a relua jocul.
	
	
	Mod de utilizare al jocului:
	1. Alegerea unui nivel de dificultate;
	
	2. Alegerea numarului de jucatori sau a optiunii de a iesi din joc; 
	
	3. P1 : misca  paleta prin apasarea tastei "A"(stanga) si "B"(dreapta);
	   P2 : misca  paleta prin apasarea tastei sageata stanga si sageata dreapta;
	   In cazul in care este ales modul "singleplayer" se va juca doar P2;
	   !!! Pe parcursul jocului se poate pune pauza prin apasarea tastei "space";
	   
	4. Reluarea jocului la acelasi nivel de dificultate.
	
	
	
	Probleme intampinate:
	- generarea mingii de pe pozitia de paleta corespunzatoare
		solutie: generarea mingii cu doua pozitii deasupra paletei corespunzatoare
		
	- reluarea jocului cu un alt nivel de dificulatate
		solutie: rularea de la inceput a programului
		
	-servirea verticala a mingii prin intermediul functiei "vertical_direction" 	
			solutie: servirea mingei cu directii "oblice" prin intermediul pozitiei de pe linie sau coloana
	

	- gasirea mijlocului paletei (locul de unde serveste mingea) 
		solutie: implementarea functiei "position" care returneaza mijlocul paletei in functie de miscarea acesteia
		
	- afisarea cursorului de fiecare data cand se redesena matricea
		solutie: implementarea functiei "hidecursor"
	
	- probleme vizuale datorate redesenarii matricei
			solutie:implementarea functiei "clean"

