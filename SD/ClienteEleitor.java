import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class ClienteEleitor {
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)){
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            ServicoDeVotacao servico = (ServicoDeVotacao) registry.lookup("SistemaVotacao");
            System.out.print("Digite seu nome: ");
            String nome = sc.nextLine();
            System.out.println("Candidatos disponíveis: [Alice, Bob, Charlie]");
            System.out.print("Seu voto: ");
            String candidato = sc.nextLine();
            servico.votar(nome, candidato);
            System.out.println("Confirmação: Voto registrado com sucesso!");
        }catch(Exception e){
            System.err.println("Erro no cliente de votação: " + e.getMessage());
        }
    }
}