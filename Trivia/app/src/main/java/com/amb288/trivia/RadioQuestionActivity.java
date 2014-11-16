package com.amb288.trivia;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.RadioButton;

/**
 * Created by a large turtle on 11/15/2014.
 */
public class RadioQuestionActivity extends Activity {

    private Button backBtn = null;
    private Button submitBtn = null;
    private TextView questionLbl = null;
    private TextView resultLbl = null;
    private RadioButton rb1 = null;
    private RadioButton rb2 = null;
    private RadioButton rb3 = null;
    private RadioButton rb4 = null;
    private RadioGroup radioGroup = null;
    private Bundle extras = null;

    private final static String TAG = "Radio Question Activity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.radio_layout);

        backBtn = (Button) findViewById(R.id.back);
        submitBtn = (Button) findViewById(R.id.submit);
        questionLbl = (TextView) findViewById(R.id.question);
        resultLbl = (TextView) findViewById(R.id.result);
        rb1 = (RadioButton) findViewById(R.id.answer1);
        rb2 = (RadioButton) findViewById(R.id.answer2);
        rb3 = (RadioButton) findViewById(R.id.answer3);
        rb4 = (RadioButton) findViewById(R.id.answer4);
        radioGroup = (RadioGroup) findViewById(R.id.radioGroup);
        extras = getIntent().getExtras();

        if (extras != null) {
            questionLbl.setText(extras.getString("question"));
            rb1.setText(extras.getStringArray("selection")[0]);
            rb2.setText(extras.getStringArray("selection")[1]);
            rb3.setText(extras.getStringArray("selection")[2]);
            rb4.setText(extras.getStringArray("selection")[3]);
            backBtn.setEnabled(false);
        }

        Button viewAnswerBtn = (Button) findViewById(R.id.submit);
        viewAnswerBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                backBtn.setEnabled(true);
                submitBtn.setEnabled(false);

                if (radioGroup.indexOfChild(findViewById(radioGroup.getCheckedRadioButtonId())) + 1 == extras.getInt("answer")) {
                    resultLbl.setText("You have answered the question correctly!");
                    setResult(RESULT_OK, null);
                }
                else {
                    resultLbl.setText("Sorry, the answer was " + getAnswer(extras.getInt("answer")));
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

    String getAnswer(int id) {
        switch(id) {
            case 1:
                return rb1.getText().toString();
            case 2:
                return rb2.getText().toString();
            case 3:
                return rb3.getText().toString();
            case 4:
                return rb4.getText().toString();
        }

        return "If you see this you have more than four values in your selection array";
    }
}
