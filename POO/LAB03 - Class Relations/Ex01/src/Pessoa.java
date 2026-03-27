public class Pessoa {
    Carro carro = new Carro();
    private String nome = "João Cleber";

    public void mostrarInformacoes(){
        System.out.println("Nome: " + nome);
        System.out.println("Modelo: " + carro.modelo);
    }
}

