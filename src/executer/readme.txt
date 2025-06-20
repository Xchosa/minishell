Hey!
Also was noch fehlt und ein kleiner abriss wie es funktioniert... 
Heredoc klappt noch nicht, hab mir das von pasha mal angeschaut aber so funktioniert es scheinbar noch nicht. Die ganzen redirections laufen darueber dass man die file
descriptoren 1 und 0 hierhin und dahin duped. und bei heredoc soll das was geschrieben wird in die STDIN_FILENO geschrieben werden aber so wie es ist reicht es nicht ...
Die redirections werden der reihe nach in der liste abgehandelt und das funktioniert ganz gut so, die O_FLAGS machen da viel arbeit. ich denke, dass heredoc auch einfach 
in dieser reihenfolge dran kommen kann und wenn was anderes kommt wird es einfach ueberschrieben, alle redirections werden so oder so behandelt bevor irgendetwas ausgefuerht wird.
Also heredoc muss nicht "als erster" kommen, glaube ich ...
ansoten hab ich in executer.c einiges kommentiert, wenn du von unten nach oben liest sollte es mit comments und einfach den funktionsnamen relativ selbst erklaerend sein. 
was sonst fehlt:
- exit codes. der von execve kann in meiner hauptfunktion abgefangen werden, alle anderen builtins schaetze ich sollten einfach die variable auf den neunen wert setzen
- free. in den funtionen wird oft ein neuer char ** erstellt fuer env und der alte muss noch gefreet werden, habs oft dazu kommentiert aber nicht zu ende gedacht. 
Und dann ist halt die frage was die builtins alles koennen sollen...
z.b. was cd nicht kann ist runter und wieder rauf also cd ../../bla/blub. wenn man das realisiseren will muss man glaube ich split benutzen und dann jeden schritt einzeln gehn,
was nicht unmoeglich ist.
export printed zwar sortiert aber nicht 100% genau wie das richtige export, habs in der funktion stehn was unterschiedlich ist. um das zu sehen kannst du es dir auch in file1 
und file2 schreiben lassen und dann diff file1 file2 ausfuehren oder so aehnlich
und so scherze wie pwd ... in der bash kann man unset PWD machen und dann funktioniert der pwd call immernoch. aber wtf?
und shell level, wobei das vllt auch unnoetig ist?
