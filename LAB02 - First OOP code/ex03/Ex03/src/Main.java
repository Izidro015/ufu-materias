public class Main {
    public static void main(String [] args){

        Candidato [] candidatos = new Candidato [3];

        candidatos[0] = new Candidato ();
        candidatos[0].setNome_completo("SALATIEL MAGALHÃES");
        candidatos[0].setData_de_Nascimento("08/02/1984");
        candidatos[0].setGenero("Masculino");
        candidatos[0].setCargo_pretendido("Prefeito");
        candidatos[0].setTotal_de_bens(450000F);
        candidatos[0].setReeleicao(false);
        candidatos[0].setNúmero_do_partido(55);

        candidatos[1] = new Candidato ();
        candidatos[1].setNome_completo("EVANDRO SILVA");
        candidatos[1].setData_de_Nascimento("08/06/1985");
        candidatos[1].setGenero("Masculino");
        candidatos[1].setCargo_pretendido("Prefeito");
        candidatos[1].setTotal_de_bens(0F);
        candidatos[1].setReeleicao(false);
        candidatos[1].setNúmero_do_partido(55);

        candidatos[2] = new Candidato ();
        candidatos[2].setNome_completo("MATHEUS FELIPE");
        candidatos[2].setData_de_Nascimento("22/05/1986");
        candidatos[2].setGenero("Masculino");
        candidatos[2].setCargo_pretendido("Prefeito");
        candidatos[2].setTotal_de_bens(1000000F);
        candidatos[2].setReeleicao(true);
        candidatos[2].setNúmero_do_partido(13);


        for(int i = 0; i < 3; i++){
            candidatos[i].mostrarInformacoes();
        }
    }
}