# PROG3Assignment

Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
Contact details: billy@caudimordax.org, joakimberglund@live.se

- Alla bild- och ljudfiler som används ligger i en mapp med namnet "res".
- Ljudformatet som används är .ogg.
- Alla bilder bör vara .png.

- Det som går att anpassa har istället för att ligga i "main.cpp" lyfts ut
  till "Invaders"-klassen. Där applikationsprogrammeraren kan ändra vissa aspekter av spelet.

- Sprites skapar objekt av "Graphic"-klassen som har en shared_ptr som ser till att
  minnet frigörs när alla instanser blivit destruerade.

- Nytt spel startas med y-tangenten, spelare 1 styrs med vänster-/högerpil eller a-/d-tangenterna
  och skjuter med vänster ctrl. Spelare 2 styrs med j-/l-tangenterna och skjuter med höger ctrl.
  Spelet avslutas med esc. F8-tangenten pausar musiken.

