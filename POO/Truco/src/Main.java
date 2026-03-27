public class Main {
    public static void main(String[] args) {
        System.out.println("=================================");
        System.out.println("    BEM-VINDO AO JOGO DE TRUCO   ");
        System.out.println("=================================");
        System.out.println();

        try {
            Jogo jogo = new Jogo();
            jogo.executarMenu();

        } catch (Exception e) {
            System.err.println("Erro fatal no programa: " + e.getMessage());
            e.printStackTrace();

            try {
                System.err.println("Tentando salvar dados de emergência...");
            } catch (Exception saveError) {
                System.err.println("Não foi possível salvar dados de emergência: "
                        + saveError.getMessage());
            }

            System.exit(1);
        } finally {
            System.out.println("\n=================================");
            System.out.println("       OBRIGADO POR JOGAR!       ");
            System.out.println("=================================");
        }
    }
}