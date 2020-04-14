package simple;

import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.HBox;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.util.Duration;

import java.text.DecimalFormat;

public class Control extends HBox {

    private final Label lbPlay = new Label("Play");

    private final Label lbTime = new Label("00:00:00/00:00:00");

    private final Label lbLeft = new Label("<<");

    private final Label lbRight = new Label(">>");

    private final Slider sdProcess = new Slider();

    private final Slider sdvolumn = new Slider();

    private MediaPlayer mdPlayer;

    private final Duration duration = new Duration(10000);

    private Double currentTime = 0.0;

    private Double endTime;

    public Control(Media media) {
        super(15);
        mdPlayer = new MediaPlayer(media);
        mdPlayer.stop();
        mdPlayer.dispose();

        //添加各种组件
        this.setAlignment(Pos.CENTER);
        this.getChildren().addAll(lbPlay,lbTime,lbLeft,sdProcess,lbRight,new Label("volumn"),sdvolumn);

        //暂停播放按钮事件
        lbPlay.setOnMouseClicked(e->{
            if (lbPlay.getText().equals("Play")){
                lbPlay.setText("Pause");
                mdPlayer.play();
            }
            else{
                lbPlay.setText("Play");
                mdPlayer.pause();
            }
        });

        //快进快退按钮事件
        lbRight.setOnMouseClicked(e->{
            mdPlayer.seek(mdPlayer.getCurrentTime().add(duration));
        });
        lbLeft.setOnMouseClicked(e->{
            mdPlayer.seek(mdPlayer.getCurrentTime().subtract(duration));
        });

        sdvolumn.setValue(50);

        sdProcess.prefWidthProperty().bind(this.widthProperty().subtract(440));
    }

    /**
     * 视频初始化
     */
    public void init(Media media, MediaView mediaView) {
        mdPlayer.stop();
        mdPlayer = new MediaPlayer(media);
        mediaView.setMediaPlayer(mdPlayer);
        lbPlay.setText("Play");
        mdPlayer.setOnReady(() -> {
            endTime = mdPlayer.getStopTime().toSeconds();
        });
        mdPlayer.setOnEndOfMedia(() -> {
            mdPlayer.stop();
            mdPlayer.seek(Duration.ZERO);
            lbPlay.setText("Play");
        });
        mdPlayer.currentTimeProperty().addListener(ov->{
            currentTime = mdPlayer.getCurrentTime().toSeconds();
            lbTime.setText(timeStr(currentTime)+"/"+timeStr(endTime));
            sdProcess.setValue(currentTime/endTime*100);
        });
        sdProcess.valueProperty().addListener(ov->{
            if (sdProcess.isValueChanging()){
                mdPlayer.seek(mdPlayer.getTotalDuration().multiply(sdProcess.getValue()/100));
            }
        });
        mdPlayer.volumeProperty().bind(sdvolumn.valueProperty().divide(100));

    }


    /**
     * 获取时间格式
     * @param seconds
     * @return
     */
    private String timeStr(Double seconds){
        Integer count = seconds.intValue();
        Integer Hours = count / 3600;
        count = count % 3600;
        Integer Minutes = count /60;
        count = count % 60;
        DecimalFormat decimalFormat = new DecimalFormat("00");
        String str = decimalFormat.format(Hours)+":"+decimalFormat.format(Minutes)+":"+decimalFormat.format(count);
        return str;
    }

    public Label getLbPlay() {
        return lbPlay;
    }

    public Label getLbLeft() {
        return lbLeft;
    }

    public Label getLbRight() {
        return lbRight;
    }

    public Slider getSdProcess() {
        return sdProcess;
    }

    public Slider getSdvolumn() {
        return sdvolumn;
    }

    public MediaPlayer getMdPlayer() {
        return mdPlayer;
    }
}
