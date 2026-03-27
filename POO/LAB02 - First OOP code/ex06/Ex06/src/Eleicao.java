public class Eleicao {
    String nome_municipio;
    int num_votantes;
    Candidato[] candidatos_eleicao;

    public Eleicao(String nome_Municipio, int num_Votantes, Candidato []candidatos){
        this.nome_municipio = nome_Municipio;
        this.num_votantes = num_Votantes;
        this.candidatos_eleicao = candidatos;
    }

    public void mostrarDados(){
        System.out.println("Nome Municipio: " + nome_municipio);
        System.out.println("Numero votantes: " + num_votantes);
        System.out.println("Candidatos: ");
        for(Candidato candidato : candidatos_eleicao){
            candidato.mostrarInformacoes();
        }
    }

    public Candidato mostrarMaiorBens(){

        float total_bens = 0;
        int num_candidato = 0;
        for(int i = 0; i < candidatos_eleicao.length; i++){
            if(candidatos_eleicao[i].total_de_bens > total_bens){
                num_candidato = i;
                total_bens = candidatos_eleicao[i].total_de_bens;
            }
        }
        return candidatos_eleicao[num_candidato];
    }

    public void CompararCandidatosBens(Candidato candidato){
        for(int i = 0; i < candidatos_eleicao.length; i++){
            if(candidato.total_de_bens == candidatos_eleicao[i].total_de_bens){
                i++;
            }
            System.out.println("O candidato "+ i +" Tem uma diferença de: " + (candidatos_eleicao[i].total_de_bens/candidato.total_de_bens)*100 + "%");
        }
    }
}



