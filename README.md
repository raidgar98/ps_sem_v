# Projekt Semestralny z Programowania Systemowego (Semestr V)
##### | [Krzysztof Mochocki](https://github.com/raidgar98) | [Michał Zapart](https://github.com/) |

<br>

![CI Build](https://github.com/raidgar98/ps_sem_v/workflows/CI%20Build/badge.svg)

<br>

## Cel Projektu
---
Stworzenie gry w statki z wykorzystaniem interfejsu sieciowego

<br>
<br>

### Instrukcja budowania
---
Poniższa komenda pobierze, skonfiguruje i zainstaluje wszystkie wymagane zależności, uruchomi testy i uruchomi aplikację

<br>
<br>

```
$ sudo \
	apt-get install -y \
		cmake make g++ gcc libboost-all-dev git libsfml-dev && \
	mkdir KM_MZ_SEM_V_IPpp_31 && \
	cd KM_MZ_SEM_V_IPpp_31 && \
	git clone https://github.com/raidgar98/ps_sem_v.git && \
	mkdir build && \
	cd build && \
	cmake ../ps_sem_v && \
	make -j$(nproc) && \
	./test/tests -l all && \
	./main
```

### Debugowanie
---
Aby móc debugować projekt należy uruchomić następującą komendę w katalogu z projektem

<br>
<br>

```
$ mkdir ../debug_build && cd ../debug_build && \
	cmake -DCMAKE_BUILD_TYPE=Debug ../ps_sem_v && \
	make -j$(nproc)
```

<br>

Po zbudowaniu projekt można bez problemu debugować, za pomocą `gdb` czy `lldb`