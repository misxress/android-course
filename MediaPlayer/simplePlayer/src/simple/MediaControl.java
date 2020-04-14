package simple;

import javafx.geometry.Pos;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;

import java.io.File;

public class MediaControl extends BorderPane {

    private final FileBar fileBar = new FileBar();

    private final MediaView mdView = new MediaView();

    private File video = new File("/data/3.mp4");

    private Media media = new Media(video.toURI().toString());

    private final Control control = new Control(media);

    public MediaControl() {
        super();
        this.setTop(fileBar);
        this.setBottom(control);
        this.setCenter(mdView);

        mdView.fitWidthProperty().bind(this.widthProperty());
        mdView.fitHeightProperty().bind(this.heightProperty().subtract(70));
        mdView.setOnMouseClicked(e->{
            if (control.getLbPlay().getText().equals("Play")){
                control.getLbPlay().setText("Pause");
                control.getMdPlayer().play();
            }
            else{
                control.getLbPlay().setText("Play");
                control.getMdPlayer().pause();
            }
        });

        fileBar.getButton().setOnMouseClicked(e->{
            File video = new File(fileBar.getTextField().getText());
            Media media = new Media(video.toURI().toString());
            control.init(media,mdView);
        });
    }
}
