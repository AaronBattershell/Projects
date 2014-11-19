package com.amb288.trivia;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

/**
 * Created by a timid badger mole on 11/15/2014.
 */
public class SpinnerQuestionActivity extends Activity {

    private Button backBtn = null;
    private Button submitBtn = null;
    private TextView questionLbl = null;
    private TextView resultLbl = null;
    private Spinner spinner = null;
    private Bundle extras = null;

    private final static String TAG = "Radio Question Activity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.spinner_layout);

        backBtn = (Button) findViewById(R.id.back);
        submitBtn = (Button) findViewById(R.id.submit);
        questionLbl = (TextView) findViewById(R.id.question);
        resultLbl = (TextView) findViewById(R.id.result);
        spinner = (Spinner) findViewById(R.id.spinnerSelection);
        extras = getIntent().getExtras();

        if (extras != null) {
            questionLbl.setText(extras.getString("question"));
            backBtn.setEnabled(false);

            /* Add string array values to our spinner object */
            ArrayAdapter dataAdapter = new ArrayAdapter(this,android.R.layout.simple_spinner_item, extras.getStringArray("selection"));
            dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            spinner.setAdapter(dataAdapter);
        }

        Button viewAnswerBtn = (Button) findViewById(R.id.submit);
        viewAnswerBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                backBtn.setEnabled(true);
                submitBtn.setEnabled(false);

                if (String.valueOf(spinner.getSelectedItem()) == String.valueOf(spinner.getItemAtPosition(extras.getInt("answer") - 1))) {
                    resultLbl.setText("You have answered the question correctly!");
                    setResult(RESULT_OK, null);
                }
                else {
                    resultLbl.setText("Sorry, the answer was " + String.valueOf(spinner.getItemAtPosition(extras.getInt("answer") - 1)));
                    setResult(RESULT_CANCELED, null);
                }
            }
        });

        Button returnBtn = (Button) findViewById(R.id.back);
        returnBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });
    }
}
