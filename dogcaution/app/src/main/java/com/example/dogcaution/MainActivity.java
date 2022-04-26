package com.example.dogcaution;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.content.ContentValues;
import android.os.AsyncTask;

import androidx.appcompat.app.AppCompatActivity;



public class MainActivity extends AppCompatActivity {


    ImageButton androidImageButton;
    TextView tv;
    TextView gang;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        androidImageButton=(ImageButton)findViewById(R.id.ib2);



        tv = findViewById(R.id.tv);
        gang = findViewById(R.id.gang);




        androidImageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String url="http://192.168.0.9/";
                NetworkTask networkTask = new NetworkTask(url, null);
                networkTask.execute();
            }
        });







    }

    public class NetworkTask extends AsyncTask<Void, Void, String> {

        private String url;
        private ContentValues values;

        public NetworkTask(String url, ContentValues values) {

            this.url = url;
            this.values = values;
        }

        @Override
        protected String doInBackground(Void... params) {

            String result;
            RequestHttpURLConnection requestHttpURLConnection = new RequestHttpURLConnection();
            result = requestHttpURLConnection.request(url, values);

            return result;
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);
            tv.setText(s);
        }
    }

}