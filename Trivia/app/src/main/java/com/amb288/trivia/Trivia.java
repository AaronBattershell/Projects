package com.amb288.trivia;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.content.Intent;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;


public class Trivia extends ActionBarActivity {
    int correct = 0, wrong = 0;

    /* Under most casts we would want a unique identifier for the startActivityForResults function
     * call but in this situation it is not needed */
    int NEW_QUESTION = 1;
    private TextView score = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_trivia);

        score = (TextView) findViewById(R.id.userScore);

        Button testActivity = (Button) findViewById(R.id.testButton);
        testActivity.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create an intent stating which Activity you would like to start
                Intent intent = new Intent(Trivia.this, RadioQuestionActivity.class);

                String[] answers = { "Alex", "Andrew", "Mike", "Riley" };
                intent.putExtra("question", "Who enjoys listening to leekspin?");
                intent.putExtra("selection", answers);
                intent.putExtra("answer", 4); /* 1 based answer index in the array */

                // Launch the Activity using the intent
                startActivityForResult(intent, NEW_QUESTION);
            }
        });
    }


    /* Receive the return results from the activities that have been called */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        /* Since all we care about is a boolean value I am disregarding the requestCode and
         * Intent variable. If the user answered the correct value then resultCode will be
         * the enum RESULT_OK */
        if (resultCode == RESULT_OK) {
            ++correct;
        }
        else {
            ++wrong;
        }

        score.setText(correct/(double)(correct+wrong) + "%");
    }
}
