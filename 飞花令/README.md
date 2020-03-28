## *任务概述*

1. 背景：央视1正在播放的诗词大会有个飞花令环节，即按照给定的文字答出包含此文字的古诗。
2. 要求：写一个Android APP，能够对比如诗三百进行全文检索，找出古诗。

## *功能设计*

程序要求输入一个文字，根据文字查找本地文件中的诗句，找出符合诗句将其储存为集合。展示在界面时给用户提供按钮，可以依次查看搜索结果。

## *详细设计*

1. 储存结构

   - 资源数据为csv格式。由行组成，每行一首诗，每行由逗号隔开，分别表示题目，朝代，作者，内容。

   - 程序中储存数据类型

     ```java
     //Poem.java
     
     import lombok.Data;
     
     @Data
     public class Poem {
     
         private String name;
     
         private String dynasty;
     
         private String author;
     
         private String content;
     
         public void format() {
             //因为csv文本中每个字段均含有引号，故将其去除
             name = name.substring(2,name.length() - 1);
             content = content.substring(1,content.length() - 1);
             dynasty = dynasty.substring(1,dynasty.length() - 1);
             author = author.substring(1,author.length() - 1);
         }
     }
     ```

2. 视图结构
   由一个搜索框SearchView，一个文本框TextView，一个按钮Button组成

3. 逻辑结构

   - 读取csv文件&搜索逻辑

     ```java
     //Search.java
     package com.example.feihualing;
     
     import com.csvreader.CsvReader;
     
     import java.io.InputStream;
     import java.nio.charset.Charset;
     import java.util.ArrayList;
     import java.util.List;
     
     
     public class Search {
     
         public static List<Poem> getPoem(InputStream is, String words) {
             List<Poem> ans = new ArrayList<Poem>();
             try {
                 CsvReader csvReader = new CsvReader(is, '\n', Charset.forName("utf-8"));//读取csv文件，以回车符为分隔标志
                 csvReader.readHeaders();//抛弃csv文件头
     
                 while (csvReader.readRecord()) {
                     String[] params = csvReader.getRawRecord().split(",");//获取该行段落
                     Poem one = new Poem();
                     if(params.length == 4){//将诗词信息储存在Poem类中
                         one.setName(params[0]);
                         one.setAuthor(params[2]);
                         one.setDynasty(params[1]);
                         one.setContent(params[3]);
                         one.format();//去除引号
                         if(one.getContent().contains(words)) {//判断是否有关键字
                             ans.add(one);//如果有添加到结果中
                         }
                     }
                 }
             }catch (Exception e) {
                 throw new RuntimeException(e);
             }
             return ans;//返回结果
         }
     }
     ```

   - 视图处理逻辑

     ```java
     //MainActivity.java
     package com.example.feihualing;
     
     import ......;
     
     public class MainActivity extends AppCompatActivity {
     
         //资源文件流
         InputStream is;
     
         //声明组件
         SearchView searchView;
         TextView textView;
         Button button;
     
         //声明参数
         String words;
         List<Poem> poems;
         int count;
     
         @Override
         protected void onCreate(Bundle savedInstanceState) {
             //初始化
             super.onCreate(savedInstanceState);
             setContentView(R.layout.activity_main);
             is = this.getResources().openRawResource(R.raw.tang);//获取csv文件输入流
             poems = new ArrayList<>();//初始化搜索结果集
     
             //获取组件句柄
             searchView = findViewById(R.id.searchView);
             textView = findViewById(R.id.textView);
             button = findViewById(R.id.button);
     
             //搜索框事件
             searchView.setSubmitButtonEnabled(true);
             searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
                 @Override
                 public boolean onQueryTextSubmit(String query) {
     
                     //初始化数据
                     words = query;
                     poems = Search.getPoem(is, words);
                     count = 0;
     
                     //刷新界面
                     update();
     
                     return false;
                 }
     
                 @Override
                 public boolean onQueryTextChange(String newText) {
                     return false;
                 }
             });
     
             //展示搜索结果的下一首诗
             button.setOnClickListener(new View.OnClickListener() {
                 @Override
                 public void onClick(View v) {
                     if(count >= poems.size() - 1){
                         return;
                     }
                     count++;
                     update();
                 }
             });
         }
     
         //刷新textView的方法
         private void update() {
     
             if(poems.size() == 0) {
                 textView.setText("未搜索到结果");
                 return;
             }
     
             Poem poem = poems.get(count);
             String display;
             display = "<big>" + poem.getName() + "</big><br>";//加入题目
             display += "<small>["+poem.getDynasty()+"]"+poem.getAuthor()+"</small><br>";//加入朝代和作者
             poem.setContent(poem.getContent().replace("。","。<br>"));//句号换为回车符
             poem.setContent(poem.getContent().replace(words,"<span style='color: red;'>"+words+"</span>"));//标红关键字
             display += poem.getContent();//加入内容
             textView.setText(Html.fromHtml(display));
         }
     }
     ```

     


## *遇到的问题/处理方式*

- 获取资源文件的输入流

  ```java
  InputStream is = getResources().openRawResource(R.xx.xxx);
  ```

- ArrayList和LinkList

  ```java
  ArrayList是数组实现，查找速度优；
  LinkList是链表实现，插入删除速度优。
  ```

- 搜索框使用SearchView

  ```java
  searchView.setSubmitButtonEnabled(Boolean);//开启搜索提交按钮
  searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String query) {
                return false;
            }//点击搜索触发事件
  
            @Override
            public boolean onQueryTextChange(String newText) {
                return false;
            }//搜索框文字改变触发事件
   });
  ```

- 通过html网页来组织textview的内容

  ```java
  textView.setText(Html.fromHtml(String html文本));
  ```

- 向TextView里添加html元素，但是不可以更改文字大小（缺陷），勉强通过\<small\>标签缩小了文字

  ```html
  <small>title</small>
  ```

- final关键字声明引用

  ```java
  final声明的引用后，引用所指向的东西不可以改变（即必须声明时初始化）
  ```

