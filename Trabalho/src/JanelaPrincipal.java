import javax.swing.*;
import java.awt.*;

public class JanelaPrincipal {
    public static void main(String[] args) {
        new TelaInicial();
    }
}

// Tela 1: Tela Inicial com botões de Cadastrar e Login
class TelaInicial extends JFrame {
    public TelaInicial() {
        setTitle("Bem-vindo ao Banco");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new FlowLayout());

        JButton btnCadastrar = new JButton("Cadastrar");
        JButton btnLogin = new JButton("Login");

        btnCadastrar.addActionListener(e -> {
            new TelaCadastro();
            dispose();
        });

        btnLogin.addActionListener(e -> {
            // Pseudocódigo para o Feupe implementar abaixo
            JOptionPane.showMessageDialog(null, "Chamar método de verificação de login aqui.");
        });

        add(btnCadastrar);
        add(btnLogin);

        setVisible(true);
    }
}

// Tela 2: Cadastro de novo usuário
class TelaCadastro extends JFrame {
    public TelaCadastro() {
        setTitle("Cadastro de Usuário");
        setSize(400, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(8, 2, 5, 5));

        add(new JLabel("Nome Completo:"));
        JTextField txtNome = new JTextField();
        add(txtNome);

        add(new JLabel("CPF:"));
        JTextField txtCpf = new JTextField();
        add(txtCpf);

        add(new JLabel("Endereço Completo:"));
        JTextField txtEndereco = new JTextField();
        add(txtEndereco);

        add(new JLabel("Estado Civil:"));
        JTextField txtEstadoCivil = new JTextField();
        add(txtEstadoCivil);

        add(new JLabel("Escolaridade:"));
        JTextField txtEscolaridade = new JTextField();
        add(txtEscolaridade);

        add(new JLabel("Data de Nascimento:"));
        JTextField txtDataNascimento = new JTextField();
        add(txtDataNascimento);

        JButton btnConfirmar = new JButton("Confirmar Cadastro");
        btnConfirmar.addActionListener(e -> {
            // Aqui salvaria os dados (você pode implementar com arquivos ou banco depois)
            JOptionPane.showMessageDialog(null, "Cadastro realizado com sucesso!");
            new TelaOperacoes();
            dispose();
        });
        add(btnConfirmar);

        JButton btnVoltar = new JButton("Voltar");
        btnVoltar.addActionListener(e -> {
            new TelaInicial();
            dispose();
        });
        add(btnVoltar);

        setVisible(true);
    }
}

// Tela 3: Operações bancárias
class TelaOperacoes extends JFrame {
    public TelaOperacoes() {
        setTitle("Operações Bancárias");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(4, 1, 10, 10));

        JButton btnSaque = new JButton("Saque");
        JButton btnDeposito = new JButton("Depósito");
        JButton btnPagamento = new JButton("Pagamento");
        JButton btnTransferencia = new JButton("Transferência");

        btnSaque.addActionListener(e -> JOptionPane.showMessageDialog(null, "Função de saque chamada."));
        btnDeposito.addActionListener(e -> JOptionPane.showMessageDialog(null, "Função de depósito chamada."));
        btnPagamento.addActionListener(e -> JOptionPane.showMessageDialog(null, "Função de pagamento chamada."));
        btnTransferencia.addActionListener(e -> JOptionPane.showMessageDialog(null, "Função de transferência chamada."));

        add(btnSaque);
        add(btnDeposito);
        add(btnPagamento);
        add(btnTransferencia);

        setVisible(true);
    }
}
// Tela 4: Tela de Login com nome da conta e senha
class TelaLogin extends JFrame{
    public TelaLogin() {
        setTitle("Login da Conta");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(3, 2, 5, 5));

        add(new JLabel("Nome da Conta:"));
        JTextField txtNomeConta = new JTextField();
        add(txtNomeConta);

        add(new JLabel("Senha:"));
        JPasswordField txtSenha = new JPasswordField();
        add(txtSenha);

        JButton btnEntrar = new JButton("Entrar");
        btnEntrar.addActionListener(e -> {
            String nomeConta = txtNomeConta.getText();
            String senha = new String(txtSenha.getPassword());

            /*if (verificarLogin(nomeConta, senha)) {
                JOptionPane.showMessageDialog(null, "Login realizado com sucesso!");
                new TelaOperacoes();
                dispose();
            } else {
                JOptionPane.showMessageDialog(null, "Nome da conta ou senha incorretos.");
            }*/
        });
        add(btnEntrar);

        JButton btnVoltar = new JButton("Voltar");
        btnVoltar.addActionListener(e -> {
            new TelaInicial();
            dispose();
        });
        add(btnVoltar);

        setVisible(true);

        /*private boolean verificarLogin(String numeroConta, String senha) {
            // Contas válidas para teste
            String[][] contasValidas = {
                    {"123", "senha123"},
                    {"456", "abc456"},
                    {"789", "teste789"}
            };

            for (String[] conta : contasValidas) {
                if (conta[0].equals(numeroConta) && conta[1].equals(senha)) {
                    return true;
                }
            }

            return false;
            }*/

        }
    }
