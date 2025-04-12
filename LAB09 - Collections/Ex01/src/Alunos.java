import java.util.ArrayList;

public class Alunos {
    public static void criarAlunos() {
        ArrayList<Estudante> alunos = new ArrayList<>();
        Estudante e1 = new Estudante ("José", "Rua do joca");
        Estudante e2 = new EstudanteGraduacao("João", "RUssia", "baboi");
        Estudante e3 = new EstudantePosGrad("Carla", "Tim Maia", "macarrao", "tigela");
        Estudante e4 = new EstudanteMestrado("Cleber", "B", "T", "Y", "U", "TR");
        Estudante e5 = new EstudanteDoutorado("Maria", "C", "C", "C", "C");
        alunos.add(e1);
        alunos.add(e2);
        alunos.add(e3);
        alunos.add(e4);
        alunos.add(e5);
        for(Estudante e : alunos){
          e.print();
        }
        /*for (int i = 0; i < alunos.size(); i++){
            alunos.get(i).print();
        }*/
    }

    public static void main (String args []){
        criarAlunos();
    }
}
