public class Departamento {
    private String nome_depart = "FACOM";
    Universidade universidade;

    public Departamento(Universidade uni){
        this.universidade = uni;
    }

    public void mostrarInformacoes(){
        System.out.println("Universidade: " + universidade.nome);
        System.out.println("Departamento: " + nome_depart);
    }
}
