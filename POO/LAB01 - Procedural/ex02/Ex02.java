import java.util.Scanner;

public class Ex02 {
    // Função alteraPreco
    public static boolean alteraPreco(float[] preco, int index, float porcentagem) {
        if (porcentagem > -100) {
            preco[index] *= (1 + porcentagem / 100);
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String[] nome = new String[4];
        float[] preco = new float[4];
        int[] qtdEstoque = new int[4];

        // Solicita entrada apenas para o primeiro produto
        System.out.println("\nInforme o nome, o preço e a quantidade em estoque do produto 1:");
        nome[0] = sc.nextLine();
        preco[0] = sc.nextFloat();
        qtdEstoque[0] = sc.nextInt();

        // Define valores fixos para os demais produtos
        nome[1] = "Produto B";
        preco[1] = 200f;
        qtdEstoque[1] = 20;

        nome[2] = "Produto C";
        preco[2] = 300f;
        qtdEstoque[2] = 30;

        nome[3] = "Produto D";
        preco[3] = 400f;
        qtdEstoque[3] = 40;

        // Aplicando alterações de preço
        System.out.println("\nAumentando o preço em 10% do produto 1 e 3");
        alteraPreco(preco,0,10);
        alteraPreco(preco, 2, 10);

        System.out.println("\nReduzindo o preço em 5% do produto 2");
        if (!alteraPreco(preco, 1, -5)) {
            System.out.println("\nErro: preço não alterado. Porcentagem inválida");
        } else {
            System.out.println("\nPreço alterado com sucesso");
        }

        System.out.println("\nAlterando o preço do produto 4");
        if (!alteraPreco(preco, 3, -110)) {
            System.out.println("\nErro: preço do produto 4 não alterado. Porcentagem inválida");
        }

        // Exibe os produtos cadastrados
        System.out.println("\nProdutos Cadastrados:");
        for (int i = 0; i < 4; i++) {
            System.out.printf("\nProduto: %s\nPreço: %.2f\nEstoque: %d\n", nome[i], preco[i], qtdEstoque[i]);
        }

        sc.close();
    }
}
