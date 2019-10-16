package com.example.helloneon;
import androidx.annotation.Keep;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.FileOutputStream;


public class HelloNeon extends AppCompatActivity {
    FileOutputStream outputStream;

    //String filename = "/data/user/0/com.example.helloneon/files/sign1.dat";
    String filename = "sign1.dat";
    //String fileContents = "Test Message!";

    private EditText mTextData;
    TextView tv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hello_neon);
        Log.d("File Directory", getApplicationContext().getFilesDir().toString());
        Log.d("Cache Directory", getApplicationContext().getCacheDir().toString());
        tv = findViewById(R.id.text_view_hello_neon);
        mTextData = findViewById(R.id.et_textdata);

        /*
        ((TextView)findViewById(R.id.text_view_hello_neon))
                .setText(stringFromJNI());  */
        new doWork().execute("");
    }

    /*called from c code*/
    @Keep
    public  void updateSign(final String  line) {

        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                HelloNeon.this.tv.setText(line);
            }
        });
    }


    int lineCount = 10;
    int lineLength = 24;

    protected static String padRight(String s, String pad, int n) {
        String returnValue;

        returnValue =  String.format("%-" + n + "s", s);

        if (pad != " ") {
            returnValue = returnValue.replace(" ", pad);
        }

        if (returnValue.length() > n ) {
            returnValue = returnValue.substring(0, n);
        }
        return returnValue;
    }

    protected static String join( String delim, String [] arr){

        String returnValue = "";
        for (int i = 0; i < arr.length; i ++){
            returnValue = returnValue + arr[i];
            if (i < arr.length - 1 ) {
                returnValue = returnValue + delim;
            }

        }


        return returnValue;
    }

    void formatText(){
        String mlines = mTextData.getText().toString()  ;
        String [] splitData;
        splitData = mlines.split("\n") ;

        String [] formatedsplit = new String[10] ;


        for (int j = 0; j < splitData.length & j < 10 ; j ++ ){
            if (splitData [j].length() > lineLength)  {
                formatedsplit [j] = splitData [j].substring(0, lineLength);
            }
            else if (splitData [j].length() < lineLength) {
                formatedsplit [j] = padRight (splitData[j], " ", lineLength);
            }
            else {
                formatedsplit [j] = splitData[j];
            }

        }

        for (int j = splitData.length;  j < 10 ; j ++ ) {

            formatedsplit [j] = padRight (" " , " ", lineLength);
        }

        mlines = join( "\n", formatedsplit) ;
        mlines = mlines.toUpperCase();
        mTextData.setText(mlines);
    };

    public void Save(View view) {
        formatText();

        try {
            outputStream = openFileOutput(filename, Context.MODE_PRIVATE);
            outputStream.write(mTextData.getText().toString().getBytes());
            outputStream.close();
        }catch(Exception e) {
            e.printStackTrace();

            Toast.makeText(this,"save error", Toast.LENGTH_LONG);
        }


    }


    public native String stringFromJNI();


    public class doWork extends AsyncTask<String, Void, String[]> {

        @Override
        protected void onPreExecute() {
        }

        @Override
        protected String[] doInBackground(String... params) {

            while (true) {

                stringFromJNI();
            }
            // return null;
        }

        @Override
        protected void onPostExecute(String[] passedData) {
        }

    }




    static {
        System.loadLibrary("hello-neon");
    }
}

