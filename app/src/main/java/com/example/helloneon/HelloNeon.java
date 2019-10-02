package com.example.helloneon;

import androidx.annotation.Keep;
import androidx.appcompat.app.AppCompatActivity;

import android.os.AsyncTask;
import android.os.Bundle;
import android.widget.TextView;

public class HelloNeon extends AppCompatActivity {

    TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hello_neon);

        tv = findViewById(R.id.text_view_hello_neon);
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

