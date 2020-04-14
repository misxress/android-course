package simple;

import javafx.scene.control.*;
import javafx.scene.layout.HBox;

public class FileBar extends HBox {

    private final TextField textField = new TextField();

    private final Button button = new Button("open");

    public FileBar() {
        super(2);
        button.setPrefWidth(70);
        this.getChildren().addAll(textField,button);
        textField.prefWidthProperty().bind(this.widthProperty().subtract(70));
    }

    public TextField getTextField() {
        return textField;
    }

    public Button getButton() {
        return button;
    }
}
