*Abandoned Project. Maybe one day i refact this project*

Trabalho de reconhecimento de poligonos usando a biblioteca opencv em C
Feito por Rennê da Silva Lou para a materia de Processamento de sinais II no CEFET/RJ

Dependências: g++ - compilador de C++
	      Cmake -  gerador de projetos em C cross-plataform
	      opencv - biblioteca de processamento de imagens

	      OBS: em algumas distribuições linux será necessario instalar os pacotes hdf5 e vtk, fique atento em erros durante a compilação

Compilando:
	Apos extrair os arquivos para o diretorio (que chamaremos de PATH_TO_SOME_DIRECTORY) de interesse execute os seguintes comandos
	cd /PATH_TO_SOME_DIRECTORY/
	cmake ./
	make

	sera gerado um binario chamado rehexa, para executar o programa basta dar o seguinte comando

	./rehexa PATH_TO_SOME_IMAGE
