#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <locale.h>

using namespace std;


struct Log {
	
	int id; // valor chave
	char data[10]; // xx/xx/xx
	char hora[6]; // xx:xx
	char tipo[8]; // PERDA para perda de v�deo e DETEC para detec��o de movimento
	
}; // 28 bytes 


// nome do arquivo bin
const string ARQ = "log.dat";

/*

	Essa fun��o � utilizada para checar se o ID j� existe no arquivo ou � menor que 0
	Retorna -1 caso seja menor que 0
	Retorna 1 caso ela encontra a id no arquivo
	Retorna 0 caso ela n�o encontre a id no arquivo

*/
int verificaId(int id){
	
	int tam, aux = -1, paraOlaco = 0;
	
	if(id < 0){
		
		return -1;
		
	}

	// chama o arquivo
	fstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e saida de dados para o arquivo do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::out  | ios::binary);
	
	if(file.is_open()){

		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);

        while ((file.tellg() < tam) && (paraOlaco == 0)) {
        	
            // captura do arquivo e salva na struct
            file.read((char*)&evento, sizeof(Log));
            
            // testa se a id do arquivo � igual a que foi inserida
            if (evento.id == id) {
                paraOlaco = 1;
                
            }
            
            // variavel que auxialiar� na sobreposi��o
            aux++;
            
        }		
        
        if (paraOlaco == 1) {                      
                                 
            file.close();
            
            return 1;
            
        }
		
		else {            
            return 0;
            
        }	
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}
	
	
}

/*

	Captura a entrada de dados e salva em uma struct
	Retorna a struct com os dados salvos nela

*/
Log capturaDados(){
	
	// struct
	Log evento;
		
	system("cls");
	cout << endl << "\t" << ">>>> Captura dados <<<<" << "\t" << endl;
	cout << endl;
	
	cout << "Informe a ID: ";
	cin >> evento.id;	
	
	cin.ignore();
		
	cout << endl << endl << "[PERDA] = Perda de v�deo || [DETEC] Detec��o de movimento" << endl;
	cout << "Informe o tipo de evento: ";
	gets(evento.tipo);		
	
	cout << endl << endl << "Exemplo de data: XX/XX/XX" << endl;
	cout << "Insira a data: ";
	gets(evento.data);			
			
	cout << endl << endl << "Exemplo de hora: XX:XX" << endl;
	cout << "Insira a data: ";	
	gets(evento.hora);
	
	return evento;
	
} 

/*

	Captura a entrada de dados e salva em uma struct
	Retorna a struct com os dados salvos nela
	
	Utilizada para alterar dados, apenas inclui novo(a) nas saidas para a tela

*/
Log capturanovoDados(){
	
	// struct
	Log evento;
		
	system("cls");
	cout << endl << "\t" << ">>>> Captura novos dados <<<<" << "\t" << endl;
	cout << endl;
	
	cout << "Informe a nova ID: ";
	cin >> evento.id;	
	
	cin.ignore();
		
	cout << endl << endl << "[PERDA] = Perda de v�deo || [DETEC] Detec��o de movimento" << endl;
	cout << "Informe o novo tipo de evento: ";
	gets(evento.tipo);		
	
	cout << endl << endl << "Exemplo de data: XX/XX/XX" << endl;
	cout << "Insira a nova data: ";
	gets(evento.data);			
			
	cout << endl << endl << "Exemplo de hora: XX:XX" << endl;
	cout << "Insira a nova data: ";	
	gets(evento.hora);
	
	return evento;
	
} 

/*

	Ap�s todas as intera��es da main(), o usuario tem a op��o de sair ou voltar ao menu
	Essa fun��o pega o dado do usuario e devolve o valor para ser tratado

*/
int chamaMenu(){
	
	int x;
	
	cout << "0 - Menu principal" << endl;
	cout << "99 - Sair" << endl;
	cout << endl;
	cout << "Digite a opcao desejada: ";
	cin >> x;
	
	return x;
}
	

/*

	Ap�s salvar as informa��es na struct e confirmar que a ID n�o est� duplicada, essa fun��o � chamada
	Recebendo a pr�pria struct como parametro, ela simpleste adiciona ao final do arquivo
	Retorna 1 se sucesso
	Retorna 0 se sem sucesso

*/
int escreveDados(Log evento){
	
	// saida para o arquivo 
	ofstream file;
	
	// abre o arquivo log.dat para saida de dados, do tipo bin�rio e para inser��o ao final
	file.open(ARQ.c_str(), ios::out | ios::binary | ios::app);
	
	// se arquivo estiver aberto, escreve os dados da struct no arquivo e fecha
	if(file.is_open()){
		
		file.write((char*)&evento, sizeof(Log));
		
		file.close();
		
		return 1;
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}
	
}


/*

	Mostra em tela todos os registro que tem ID diferente de -1
	Retorna 1 se sucesso
	Retorna 0 se sem sucesso

*/
int listarLogico(){
	
	// entrada para a programa
	ifstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::binary);
	
	// se arquivo estiver aberto, escreve os dados da struct no arquivo e fecha
	if(file.is_open()){
		
		int tam;
		
		// struct para receber os registros
		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);
		
		// tabela��o para exibir a lista
		cout << "ID" << "\t" << "TIPO" << "\t" << "DATA" << "\t\t" << "HORA" << endl;	
		
		while(file.tellg() < tam){
			
			// pega um registro do arquivo
            file.read((char*)&evento, sizeof(Log));
            
            if(evento.id != -1){
			
	            // Mostra o registro em tela                
	            cout << evento.id << "\t" << evento.tipo << "\t" << evento.data << "\t" << evento.hora << endl;	
						
			}
		}
		
		file.close();
		
		return 1;
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}
	
	
	
}


/*

	Mostra em tela todos os registros
	Retorna 1 se sucesso
	Retorna 0 se sem sucesso

*/
int listarFisico(){
	
	// entrada para a programa
	ifstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::binary);
	
	// se arquivo estiver aberto, escreve os dados da struct no arquivo e fecha
	if(file.is_open()){
		
		int tam;
		
		// struct para receber os registros
		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);
		
		// tabela��o para exibir a lista
		cout << "ID" << "\t" << "TIPO" << "\t" << "DATA" << "\t\t" << "HORA" << endl;	
		
		while(file.tellg() < tam){
			
			// pega um registro do arquivo
            file.read((char*)&evento, sizeof(Log));
            
            // Mostra o registro em tela                
            cout << evento.id << "\t" << evento.tipo << "\t" << evento.data << "\t" << evento.hora << endl;			
			
		}
		
		file.close();
		
		return 1;
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}
	
	
}

/*

	Conta a quantidade de registros com ID diferente de -1
	Retorna i que � a quantidade de linhas com id diferente de -1
	Retorna 0 se sem sucesso
	
*/
int qtdeReg(){
	
	// entrada para a programa
	ifstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::binary);
	
	// se arquivo estiver aberto, calculo a qtde e fecha
	if(file.is_open()){

		int tam, i=0;
		
		// struct para receber os registros
		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);	
		
		while(file.tellg() < tam){
			
			// pega um registro do arquivo
            file.read((char*)&evento, sizeof(Log));
		
			if(evento.id !=-1){
				i++;
			}
			
		}
		
		file.close();
		
		return i;
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}	
	
}

/*

	Utilizado apenas na fun��o retornaProp para que retorne o tamanho do arquivo 

*/
int tamReg(){
	
	// ID = 4 bytes
	// DATA = 10 bytes
	// HORA = 6 bytes
	// TIPO = 8 bytes
	// TOTAL = 28 bytes

	return (28);
}

/*

	Informa a quantidade de registros, o tamanho de cada registro e o tamanho do arquivo
	Retorna 1 se sucesso
	Retorna 0 se sem sucesso

*/
int retornaProp(){

	// entrada para a programa
	ifstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::binary);
	
	// se arquivo estiver aberto, calculo o tamanho e fecha
	if(file.is_open()){

		int arq, qtde, tam;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		arq = file.tellg();		
		
		// calcula a quantidade de registros
		qtde = qtdeReg();
		if(qtde < 0){
			cout << endl << "Ops, tivemos algum erro ao calcular a quantidade de registros" << endl;
			
			return 0;
			
		}
		
		// calcula o tamanho dos registros
		tam = tamReg();
		if(tam != 28){
			cout << endl << "Ops, tivemos algum erro ao calcular o tamanho de cada registro" << endl;
			
			return 0;
			
		}
		
		// mostra na tela			
		cout << "Quantidade de registros: " << qtde << endl;
		
		cout << endl << "Tamanho de cada registro: " << tam << " bytes"  << endl;
		
		cout << endl << "Tamanho do arquivo: " << arq << " bytes" << endl;
		
		file.close();
		
		return 1;
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}
		
}

/*

	Exclus�o de um registro a partir de um ID, essa exclus�o � l�gica ent�o a ID do registro ser� marcada como -1
	Retorna 1 se sucesso
	Retorna 0 se sem sucesso

*/
int excluiId(){
	
	int idExcluir, tam, aux = -1, paraOlaco = 0;
	
	system("cls");
	cout << endl << "\t" << ">>>> Excluir por ID <<<<" << "\t" << endl;
	cout << endl;	
	
	cout << "Entre com a ID: ";
	cin >> idExcluir;
	
	// chama o arquivo
	fstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e saida de dados para o arquivo do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::out  | ios::binary);
	
	if(file.is_open()){

		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);

        while ((file.tellg() < tam) && (paraOlaco == 0)) {
        	
            // captura do arquivo e salva na struct
            file.read((char*)&evento, sizeof(Log));
            
            // testa se a id do arquivo � igual a que foi inserida
            if (evento.id == idExcluir) {
                paraOlaco = 1;
                
            }
            
            // variavel que auxialiar� na sobreposi��o
            aux++;
            
        }		
        
        if (paraOlaco == 1) {
        	
            // define a id do registro para -1 = excluido
            evento.id = -1;
            
            //Posiciona no registro a ser alterado
            file.seekg(aux * tamReg());
            
            // escreve o mesmo registro mas agora com -1 na id
            file.write((char*)&evento, sizeof(Log));            
            
            file.close();
            
            return 1;
            
        }
		
		else {
			
			cout << endl;
            cout << "Ops, o registro n�o foi encontrado" << endl;
            
            return 0;
            
        }	
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}
	
	
}

/*

	Exclus�o de registro a partir do TIPO, essa fun��o procura a primeira apari��o do TIPO que n�o esteja deletado e marca como -1 a ID para exclus�o l�gica
	
	Exemplo:
	
		ID 	TIPO 
		-1	PERDA <~~ n�o muda pois j� tem -1 na ID
		10	PERDA <~~ primeira apari��o do TIPO com a ID diferente de -1, ent�o deleta logicamente
		
	Retorna 1 se sucesso
	Retorna 0 se sem sucesso						

*/
int excluiTipo(){
	
	int tam, aux = -1, paraOlaco = 0;
	char tipoExcluir[8];
	
	system("cls");
	cout << endl << "\t" << ">>>> Excluir por TIPO <<<<" << "\t" << endl;
	cout << endl;	
	
	cout << "[PERDA] = Perda de v�deo || [DETEC] Detec��o de movimento" << endl;
	cout << "Entre com o TIPO: ";
	cin.ignore();
	gets(tipoExcluir);
	
	// chama o arquivo
	fstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e saida de dados para o arquivo do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::out  | ios::binary);
	
	if(file.is_open()){

		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);

        while ((file.tellg() < tam) && (paraOlaco == 0)) {
        	
            // captura do arquivo e salva na struct
            file.read((char*)&evento, sizeof(Log));
            
            
            if (strcmp(evento.tipo, tipoExcluir) == 0) {
                paraOlaco = 1;               
                                
            }
            
            // variavel que auxialiar� na sobreposi��o
            aux++;
            
        }		
        
        if (paraOlaco == 1) {
        	
            // define a id do registro para -1 = excluido
            evento.id = -1;
            
            //Posiciona no registro a ser alterado
            file.seekg(aux * tamReg());
            
            // escreve o mesmo registro mas agora com -1 na id
            file.write((char*)&evento, sizeof(Log));            
            
            file.close();
            
            return 1;
            
        }
		
		else {
			
			cout << endl;
            cout << "Ops, o registro n�o foi encontrado" << endl;
            
            return 0;
            
        }	
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}	
	
}


/*

	Altera��o de registro a partir da ID, antes de fazer a altera��o com os novos dados inseridos pelo usuario testa se a ID j� existe e se existir n�o far� altera��o
	Retorna 1 se sucesso
	Retorna 0 se sem sucesso

*/
int alterarId(){
	
	int idAlterar, tam, aux = -1, paraOlaco = 0;

	system("cls");
	cout << endl << "\t" << ">>>> Alterar por ID <<<<" << "\t" << endl;
	cout << endl;	
	
	cout << "Entre com a ID: ";
	cin >> idAlterar;
	
	if(idAlterar == -1){
		
		return -1;
		
	}

	// chama o arquivo
	fstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e saida de dados para o arquivo do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::out  | ios::binary);
	
	if(file.is_open()){

		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);

        while ((file.tellg() < tam) && (paraOlaco == 0)) {
        	
            // captura do arquivo e salva na struct
            file.read((char*)&evento, sizeof(Log));
            
            // testa se a id do arquivo � igual a que foi inserida
            if (evento.id == idAlterar) {
                paraOlaco = 1;
                
            }
            
            // variavel que auxialiar� na sobreposi��o
            aux++;
            
        }		
        
        if (paraOlaco == 1) {
        	
        	// variavel p pegar o retorno da fun��o
        	int chamaverificaId;
        	
        	// chama fun��o para pegar dados e armanezar na variavel
            evento = capturanovoDados();
            
            // chama a fun��o e salva na variavel para tratarmos as saidas
            chamaverificaId = verificaId(evento.id);            
            
			if(chamaverificaId == -1){
				
				return -1;
				
			}
			else if (chamaverificaId == 1){
				
				return 2;
				
			}         
            
            //Posiciona no registro a ser alterado
            file.seekg(aux * tamReg());
            
            // escreve o mesmo registro mas agora com -1 na id
            file.write((char*)&evento, sizeof(Log));            
            
            file.close();
            
            return 1;
            
        }
		
		else {
			
			cout << endl;
            cout << "Ops, o registro n�o foi encontrado" << endl;
            
            return 0;
            
        }	
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}


}


/*

	Altera��o de registro a partir do TIPO, antes de fazer a altera��o com os novos dados inseridos pelo usuario testa se a ID j� existe e se existir n�o far� altera��o
	Retorna 1 se sucesso
	Retorna 0 se sem sucesso

*/
int alterarTipo(){
	
	int tam, aux = -1, paraOlaco = 0;
	char tipoAlterar[8];
	
	system("cls");
	cout << endl << "\t" << ">>>> Alterar por TIPO <<<<" << "\t" << endl;
	cout << endl;	
	
	cout << "[PERDA] = Perda de v�deo || [DETEC] Detec��o de movimento" << endl;
	cout << "Entre com o TIPO: ";
	cin.ignore();
	gets(tipoAlterar);
	
	// chama o arquivo
	fstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e saida de dados para o arquivo do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::out  | ios::binary);
	
	if(file.is_open()){

		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);

        while ((file.tellg() < tam) && (paraOlaco == 0)) {
        	
            // captura do arquivo e salva na struct
            file.read((char*)&evento, sizeof(Log));
            
            
            if ((strcmp(evento.tipo, tipoAlterar) == 0) && (evento.id != -1))  {
                paraOlaco = 1;               
                                
            }
            
            // variavel que auxialiar� na sobreposi��o
            aux++;
            
        }		
        
        if (paraOlaco == 1) {
        	
            // variavel p pegar o retorno da fun��o
        	int chamaverificaId;
        	
        	// chama fun��o para pegar dados e armanezar na variavel
            evento = capturanovoDados();
            
            // chama a fun��o e salva na variavel para tratarmos as saidas
            chamaverificaId = verificaId(evento.id);            
            
			if(chamaverificaId == -1){
				
				return -1;
				
			}
			else if (chamaverificaId == 1){
				
				return 2;
				
			}   
            
            //Posiciona no registro a ser alterado
            file.seekg(aux * tamReg());
            
            // escreve o mesmo registro mas agora com -1 na id
            file.write((char*)&evento, sizeof(Log));            
            
            file.close();
            
            return 1;
            
        }
		
		else {
			
			cout << endl;
            cout << "Ops, o registro n�o foi encontrado" << endl;
            
            return 0;
            
        }	
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}
	
}


/*

	Realiza uma consulta no arquivo e mostra o registro que tiver a ID correspondente
	Retorna 1 se sucesso e 0 se sem sucesso

*/
int consultaId(){

	int idConsultar, tam, aux = -1, paraOlaco = 0;

	system("cls");
	cout << endl << "\t" << ">>>> Consultar por ID <<<<" << "\t" << endl;
	cout << endl;	
	
	cout << "Entre com a ID: ";
	cin >> idConsultar;
	
	if(idConsultar == -1){
		
		return -1;
		
	}

	// chama o arquivo
	fstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e saida de dados para o arquivo do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::out  | ios::binary);
	
	if(file.is_open()){

		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);

        while ((file.tellg() < tam) && (paraOlaco == 0)) {
        	
            // captura do arquivo e salva na struct
            file.read((char*)&evento, sizeof(Log));
            
            // testa se a id do arquivo � igual a que foi inserida
            if (evento.id == idConsultar) {
                paraOlaco = 1;
                
            }
            
            // variavel que auxialiar� na sobreposi��o
            aux++;
            
        }		
        
        if (paraOlaco == 1) {        	
                      
            //Posiciona no registro a ser alterado
            file.seekg(aux * tamReg());
            
            // pega um registro do arquivo
            file.read((char*)&evento, sizeof(Log));
            
            // Mostra o registro em tela                
            system("cls");
			cout << endl << "\t" << ">>>> Registro correspondente a ID <<<<" << "\t" << endl;
			cout << endl;
			
			// tabela��o para exibir a lista
			cout << "ID" << "\t" << "TIPO" << "\t" << "DATA" << "\t\t" << "HORA" << endl;
            cout << evento.id << "\t" << evento.tipo << "\t" << evento.data << "\t" << evento.hora << endl;	
                      
            
            file.close();
            
            return 1;
            
        }
		
		else {
			
			cout << endl;
            cout << "Ops, o registro n�o foi encontrado" << endl;
            
            return 0;
            
        }	
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}

}


/*

	Realiza uma consulta no arquivo e mostra o registro primeiro registro que tiver a TIPO correspondente
	Retorna 1 se sucesso e 0 se sem sucesso

*/
int consultaTipo(){
	
	int tam, aux = -1, paraOlaco = 0;
	char tipoConsulta[8];
	
	system("cls");
	cout << endl << "\t" << ">>>> Alterar por TIPO <<<<" << "\t" << endl;
	cout << endl;	
	
	cout << "[PERDA] = Perda de v�deo || [DETEC] Detec��o de movimento" << endl;
	cout << "Entre com o TIPO: ";
	cin.ignore();
	gets(tipoConsulta);
	
	// chama o arquivo
	fstream file;
	
	// abre o arquivo log.dat para entrada de dados no programa e saida de dados para o arquivo do tipo bin�rio
	file.open(ARQ.c_str(), ios::in | ios::out  | ios::binary);
	
	if(file.is_open()){

		Log evento;
		
		// fim do arquivo
		file.seekg(0, file.end);
		
		// pega o tamanho do arquivo
		tam = file.tellg();
		
		// volta para o inicio do arquivo
		file.seekg(0, file.beg);

        while ((file.tellg() < tam) && (paraOlaco == 0)) {
        	
            // captura do arquivo e salva na struct
            file.read((char*)&evento, sizeof(Log));
            
            
            if ((strcmp(evento.tipo, tipoConsulta) == 0) && (evento.id != -1))  {
                paraOlaco = 1;               
                                
            }
            
            // variavel que auxialiar� na sobreposi��o
            aux++;
            
        }		
        
        if (paraOlaco == 1) {
        	
            //Posiciona no registro a ser alterado
            file.seekg(aux * tamReg());
            
            // pega um registro do arquivo
            file.read((char*)&evento, sizeof(Log));
            
            // Mostra o registro em tela                
            system("cls");
			cout << endl << "\t" << ">>>> Registro correspondente ao TIPO <<<<" << "\t" << endl;
			cout << endl;
			
			// tabela��o para exibir a lista
			cout << "ID" << "\t" << "TIPO" << "\t" << "DATA" << "\t\t" << "HORA" << endl;
            cout << evento.id << "\t" << evento.tipo << "\t" << evento.data << "\t" << evento.hora << endl;	
         	
            
            file.close();
            
            return 1;
            
        }
		
		else {
			
			cout << endl;
            cout << "Ops, o registro n�o foi encontrado" << endl;
            
            return 0;
            
        }	
		
	}
	
	else {
		
		cout << "Ops, o arquivo n�o foi aberto" << endl;
		
		return 0;
	}
			
}


/*

	O menu principal foi desenvolvido com o um for infinito para que consigamos voltar com praticidade para o menu sem ter que chamar uma fun��o para isso
	Para sair do programa podemos utilizar um break pois saimos do la�o atual (for) e caimos no return EXIT_SUCCES

*/
int main() {
	
	// pt-br
	setlocale(LC_ALL, "Portuguese");

	int opcao = 555;
	
	for(int i=0;;){
	
		system("cls");
		cout << endl << "\t" << ">>>> Menu de op��es <<<<" << "\t" << endl;
		cout << endl;
		cout << "1 - Incluir" << endl;
		cout << "2 - Exluir l�gico" << endl;
		cout << "3 - Alterar" << endl;
		cout << "4 - Consultar" << endl;
		cout << "5 - Listar l�gico" << endl;
		cout << "6 - Listar f�sico" << endl;
		cout << "7 - Propriedades" << endl;
		cout << "99 - Sair" << endl;
		cout << endl;
		cout << "Digite a opcao desejada: ";
		cin >> opcao;	
		
		// incluir
		if(opcao == 1){
			
			// declara struct
			Log evento; 
			
			// variavel usada para pegar o retorno da fun��o
			int opcao1, chamaverificaId;
			
					
			// chama fun��o pra pegar dados
			evento = capturaDados(); 			
			
			chamaverificaId = verificaId(evento.id);
			
			if(chamaverificaId == 1){
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
				cout << "ERRO = a ID informada j� existe no arquivo" << endl << endl;;
				break;
				
			}
			
			else if(chamaverificaId == -1){
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
				cout << "ERRO = n�o � poss�vel adicionar uma ID menor que zero" << endl << endl;;
				break;
				
			}				
			
			// chama funcao para escrever no arquivo
			opcao1 = escreveDados(evento);
			
			// testa o retorno para informar ao usuario se o registro foi feito
			if(opcao1 == 1){
				
				system("cls");
				cout << endl << "\t" << ">>>> Registro inserido com sucesso <<<<" << "\t" << endl;
				cout << endl;
				
				// da opcao do usuario sair do la�o for ou simplesmente voltar ao for
				opcao1 = chamaMenu();
				
				// testa op��o do usuario, se for 0 simplesmente imprime na tela pois o for criado � infinito
				if(opcao1 == 0){
							
					system("cls");
					cout << endl << "\t" << ">>>> Retornando ao menu <<<<" << "\t" << endl;
					cout << endl;
								
				}
							
				// se for 99 encerra o programa diretamente
				else if(opcao1 == 99){
							
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado pelo usu�rio <<<<" << "\t" << endl;
					break;
								
				}
							
				// nesse ponto do programa, resolvemos encerrar caso o usuario digite algo fora do pedido
				else {
								
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
					break;
								
				}

			}
			
			// caso o return seja diferente de 1 (sucesso), informa ao usuario e tamb�m finaliza o programa
			else {
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = falha ao inserir registro no arquivo" << endl << endl;;
				break;
				
			}
			
			
		}
		// excluir
		else if(opcao == 2){
			
			int opcao2;
			
			system("cls");
			cout << endl << "\t" << ">>>> Excluir <<<<" << "\t" << endl;
			cout << endl;
			
			cout << "[1] = Por ID || [2] Por TIPO" << endl << endl;
			cout << "Informe o op��o de exclus�o: ";
			cin >> opcao2;
			
			if(opcao2 == 1){
				opcao2 = excluiId();
			}
			else if(opcao2 == 2){
				opcao2 = excluiTipo();
			}
			else{
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
				break;
				
			}

			if(opcao2 == 1){
				
				system("cls");
				cout << endl << "\t" << ">>>> Registro apagado com sucesso <<<<" << "\t" << endl;
				cout << endl;
				
				// da opcao do usuario sair do la�o for ou simplesmente voltar ao for
				opcao2 = chamaMenu();
				
				// testa op��o do usuario, se for 0 simplesmente imprime na tela pois o for criado � infinito
				if(opcao2 == 0){
							
					system("cls");
					cout << endl << "\t" << ">>>> Retornando ao menu <<<<" << "\t" << endl;
					cout << endl;
								
				}
							
				// se for 99 encerra o programa diretamente
				else if(opcao2 == 99){
							
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado pelo usu�rio <<<<" << "\t" << endl;
					break;
								
				}
							
				// nesse ponto do programa, resolvemos encerrar caso o usuario digite algo fora do pedido
				else {
								
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
					break;
								
				}

			}
			
			// caso o return seja diferente de 1 (sucesso), informa ao usuario e tamb�m finaliza o programa
			else {
								
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = falha ao apagar registro do arquivo" << endl << endl;;
				break;
				
			}			

		
			
		}
		// alterar
		else if(opcao == 3){
			
			int opcao3;
			
			system("cls");
			cout << endl << "\t" << ">>>> Alterar <<<<" << "\t" << endl;
			cout << endl;
			
			cout << "[1] = Por ID || [2] Por TIPO" << endl << endl;
			cout << "Informe o op��o de exclus�o: ";
			cin >> opcao3;
			
			if(opcao3 == 1){
				opcao3 = alterarId();
				
				if(opcao3 == -1){
					
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = n�o � poss�vel adicionar uma ID menor que zero" << endl << endl;;
					break;
					
				}
				else if(opcao3 == 2){
					
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = a ID informada j� existe no arquivo" << endl << endl;;
					break;
					
				}
				
			}
			else if(opcao3 == 2){
				opcao3 = alterarTipo();
				
				if(opcao3 == -1){
					
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = n�o � poss�vel adicionar uma ID menor que zero" << endl << endl;;
					break;
					
				}
				else if(opcao3 == 2){
					
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = a ID informada j� existe no arquivo" << endl << endl;;
					break;
					
				}
			}
			else{
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
				break;
				
			}

			if(opcao3 == 1){
				
				system("cls");
				cout << endl << "\t" << ">>>> Registro alterado com sucesso <<<<" << "\t" << endl;
				cout << endl;
				
				// da opcao do usuario sair do la�o for ou simplesmente voltar ao for
				opcao3 = chamaMenu();
				
				// testa op��o do usuario, se for 0 simplesmente imprime na tela pois o for criado � infinito
				if(opcao3 == 0){
							
					system("cls");
					cout << endl << "\t" << ">>>> Retornando ao menu <<<<" << "\t" << endl;
					cout << endl;
								
				}
							
				// se for 99 encerra o programa diretamente
				else if(opcao3 == 99){
							
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado pelo usu�rio <<<<" << "\t" << endl;
					break;
								
				}
							
				// nesse ponto do programa, resolvemos encerrar caso o usuario digite algo fora do pedido
				else {
								
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
					break;
								
				}

			}
			
			else if(opcao3 == -1){
				
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = n�o � poss�vel alterar um registro exclu�do" << endl << endl;;
				break;
			
			}
			
			// caso o return seja diferente de 1 (sucesso), informa ao usuario e tamb�m finaliza o programa
			else {
								
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = falha ao alterar registro do arquivo" << endl << endl;;
				break;
				
			}
			
		}
		// consultar
		else if(opcao == 4){

			int opcao4;
			
			system("cls");
			cout << endl << "\t" << ">>>> Consultar <<<<" << "\t" << endl;
			cout << endl;
			
			cout << "[1] = Por ID || [2] Por TIPO" << endl << endl;
			cout << "Informe o op��o de consulta: ";
			cin >> opcao4;
			
			if(opcao4 == 1){
				opcao4 = consultaId();
			}
			else if(opcao4 == 2){
				opcao4 = consultaTipo();
			}
			else{
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
				break;
				
			}

			if(opcao4 == 1){				
				
				cout << endl << "\t" << ">>>> Consulta realizada com sucesso <<<<" << "\t" << endl;
				cout << endl;
				
				// da opcao do usuario sair do la�o for ou simplesmente voltar ao for
				opcao4 = chamaMenu();
				
				// testa op��o do usuario, se for 0 simplesmente imprime na tela pois o for criado � infinito
				if(opcao4 == 0){
							
					system("cls");
					cout << endl << "\t" << ">>>> Retornando ao menu <<<<" << "\t" << endl;
					cout << endl;
								
				}
							
				// se for 99 encerra o programa diretamente
				else if(opcao4 == 99){
							
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado pelo usu�rio <<<<" << "\t" << endl;
					break;
								
				}
							
				// nesse ponto do programa, resolvemos encerrar caso o usuario digite algo fora do pedido
				else {
								
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
					break;
								
				}

			}
			
			else if(opcao4 == -1){
				
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = n�o � poss�vel consultar um registro exclu�do" << endl << endl;;
				break;
			
			}
			
			// caso o return seja diferente de 1 (sucesso), informa ao usuario e tamb�m finaliza o programa
			else {
								
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = falha ao consultar registro do arquivo" << endl << endl;;
				break;
				
			}			
			
			
		}
		// listar l�gico
		else if(opcao == 5){
			
			int opcao5;
			
			system("cls");
			cout << endl << "\t" << ">>>> Listar l�gico <<<<" << "\t" << endl;
			cout << endl;
			
			opcao5 = listarLogico();
			
			
			// testa o retorno 
			if(opcao5 == 1){				
				
				cout << endl << endl << "\t" << ">>>> Listagem l�gica feita com sucesso <<<<" << "\t" << endl;
				cout << endl;
				
				// da opcao do usuario sair do la�o for ou simplesmente voltar ao for
				opcao5 = chamaMenu();
				
				// testa op��o do usuario, se for 0 simplesmente imprime na tela pois o for criado � infinito
				if(opcao5 == 0){
							
					system("cls");
					cout << endl << "\t" << ">>>> Retornando ao menu <<<<" << "\t" << endl;
					cout << endl;
								
				}
							
				// se for 99 encerra o programa diretamente
				else if(opcao5 == 99){
							
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado pelo usu�rio <<<<" << "\t" << endl;
					break;
								
				}
							
				// nesse ponto do programa, resolvemos encerrar caso o usuario digite algo fora do pedido
				else {
								
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
					break;
								
				}

			}
			
			// caso o return seja diferente de 1 (sucesso), informa ao usuario e tamb�m finaliza o programa
			else {
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = falha ao listar registros do arquivo" << endl << endl;;
				break;
				
			}
			
		}
		// listar f�sico
		else if(opcao == 6){
			
			int opcao6;
			
			system("cls");
			cout << endl << "\t" << ">>>> Listar f�sico <<<<" << "\t" << endl;
			cout << endl;
			
			opcao6 = listarFisico();
			
			
			// testa o retorno 
			if(opcao6 == 1){				
				
				cout << endl << endl << "\t" << ">>>> Listagem f�sica feita com sucesso <<<<" << "\t" << endl;
				cout << endl;
				
				// da opcao do usuario sair do la�o for ou simplesmente voltar ao for
				opcao6 = chamaMenu();
				
				// testa op��o do usuario, se for 0 simplesmente imprime na tela pois o for criado � infinito
				if(opcao6 == 0){
							
					system("cls");
					cout << endl << "\t" << ">>>> Retornando ao menu <<<<" << "\t" << endl;
					cout << endl;
								
				}
							
				// se for 99 encerra o programa diretamente
				else if(opcao6 == 99){
							
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado pelo usu�rio <<<<" << "\t" << endl;
					break;
								
				}
							
				// nesse ponto do programa, resolvemos encerrar caso o usuario digite algo fora do pedido
				else {
								
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
					break;
								
				}

			}
			
			// caso o return seja diferente de 1 (sucesso), informa ao usuario e tamb�m finaliza o programa
			else {
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = falha ao listar registros do arquivo" << endl << endl;;
				break;
				
			}
			
			
		}
		// propriedades
		else if(opcao == 7){
			
			int opcao7;
			
			system("cls");
			cout << endl << "\t" << ">>>> Propriedades <<<<" << "\t" << endl;
			cout << endl;
			
			opcao7 = retornaProp();
			
			// testa retorno
			if(opcao7 == 1){
				
				cout << endl << endl << "\t" << ">>>> Propriedades retornadas com sucesso <<<<" << "\t" << endl;
				cout << endl;
				
				// da opcao do usuario sair do la�o for ou simplesmente voltar ao for
				opcao7 = chamaMenu();
				
				// testa op��o do usuario, se for 0 simplesmente imprime na tela pois o for criado � infinito
				if(opcao7 == 0){
							
					system("cls");
					cout << endl << "\t" << ">>>> Retornando ao menu <<<<" << "\t" << endl;
					cout << endl;
								
				}
							
				// se for 99 encerra o programa diretamente
				else if(opcao7 == 99){
							
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado pelo usu�rio <<<<" << "\t" << endl;
					break;
								
				}
							
				// nesse ponto do programa, resolvemos encerrar caso o usuario digite algo fora do pedido
				else {
								
					system("cls");
					cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl << endl;
					cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
					break;
								
				}
							
			}
			
			// caso o return seja diferente de 1 (sucesso), informa ao usuario e tamb�m finaliza o programa
			else {
				
				system("cls");
				cout << endl << "\t" << ">>>> Programa finalizado por ERRO <<<<" << "\t" << endl <<  endl;
				cout << "ERRO = falha ao retornar as propriedades" << endl << endl;;
				break;
				
			}
			
			
		}
		// sair
		else if(opcao == 99){
			
			system("cls");
			cout << "PROGRAMA FINALIZADO PELO USU�RIO" << endl << endl;
			break;
			
		}
		// op��o inv�lida
		else{
			
			system("cls");
			cout << "PROGRAMA INTERROMPIDO POR ERRO" << endl << endl;
			cout << "ERRO = � necess�rio digitar uma op��o v�lida" << endl << endl;;
			break;	
					
		}

	}


	return EXIT_SUCCESS;

}
