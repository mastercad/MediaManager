---------------------------------------------------------------------------------------------------
Es gibt 2 Datenbanken
    - eine im Memory
    - eine statische auf der Platte

Soll etwas ohne collection gespeichert werden, wird nach der Collection gefragt diese angelegt (wenn sie bereits existiert wird gefragt ob die neuen
dateien hinzugefügt werden sollen) und die Dateien aus dem Memory in die Datenbank abgelegt.

Der Memory wird darauf hin entfernt und alle Änderungen gehen nur noch in die statische DB.

Wird eine Collection geöffnet, wird nur in der statischen DB gearbeitet.

Vielleicht sollten alle "nicht gespeicherten" Änderungen nur im Memory vorgehalten werden und erst beim Speichern abgelegt? Dafür kann man die
File Entities alle in eine Collection ablegen und die geänderten mit "changed" oder einem ähnlichen Flag markieren.

Die Collection für das persistieren der File Entities wäre hier am sinnvollsten ein Model, was ebenfalls in der TableView hinterlegt ist.

Die settings habe ich als key => value einträge geplant. das macht es aber alles sehr kompliziert in meinen augen. ich bräuchte noch eine SettingsCollection wo
ich alle settings dann persistiere und das bräuchte ich pro file und pro collection. und ich müsste ständig alle einträge durchlaufen um je nach priorität den
aktiven zu finden. daher werde ich hier wahrscheinlich eher auf ein entity gehen, in dem verschiedene settings stehen und das so analog in der DB umsetzen.

