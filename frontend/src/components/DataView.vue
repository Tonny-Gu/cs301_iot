<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card
          dark
          color="deep-purple accent-1"
          class="mb-2"
        >
          <v-card-title class="font-weight-light">
            <v-icon
              large
              left
              v-if="latestLux < 20"
            >
              mdi-weather-night
            </v-icon>
            <v-icon
              large
              left
              v-else
            >
              mdi-white-balance-sunny
            </v-icon>
            <v-spacer />
            <span class="display-2 font-weight-light mr-2">{{ Math.round(latestLux) }} <small>&percnt;</small></span>
          </v-card-title>
          <v-card-text>
            <div class="title">
              Current illuminance
            </div>
            <v-icon
              small
              left
            >
              mdi-clock
            </v-icon>
            <span class="caption">Last update: {{ ago }} ago</span>
          </v-card-text>
          <v-fab-transition>
            <v-btn
              color="deep-purple accent-4"
              dark
              fab
              absolute
              bottom
              right
              @click="updateLatest"
            >
              <v-icon>mdi-update</v-icon>
            </v-btn>
          </v-fab-transition>
        </v-card>

        <v-card
          flat
          tile
        >
          <v-card-title>History</v-card-title>
          <v-card-subtitle>An hour before {{ dateDisplay(selectedMoment) }}</v-card-subtitle>
          <v-card-text>
            <trend-chart
              ref="chart"
              id="history-chart"
              :min="0"
              :max="100"
              :datasets="[{
                data: values,
                smooth: true,
                fill: true,
                showPoints: true,
                className: 'brightness-curve',
              }]"
              :grid="{
                verticalLines: true,
                horizontalLines: true,
              }"
              :labels="{
                xLabels: timeLabels,
                yLabels: 5,
                yLabelsTextFormatter: n => Math.round(n) + '%',
              }"
            />
          </v-card-text>

          <v-card-actions>
            <v-spacer />

            <!--<v-dialog
              ref="dialog"
              :return-value.sync="selectedMoment"
              v-model="modal"
              persistent
              width="290px"
            >
              <template v-slot:activator="{ on }">
                <v-btn
                  icon
                  v-on="on"
                >
                  <v-icon>mdi-clock</v-icon>
                </v-btn>
              </template>
              <v-date-picker
                v-model="selectedMoment"
                scrollable
                :allowed-dates="allowPast"
              >
                <v-spacer />
                <v-btn
                  text
                  color="secondary"
                  @click="modal = false"
                >
                  Cancel
                </v-btn>
                <v-btn
                  text
                  color="primary"
                  @click="$refs.dialog.save(selectedMoment)"
                >
                  OK
                </v-btn>
              </v-date-picker>
            </v-dialog> -->
            <v-btn
              icon
              @click="backwardTime"
            >
              <v-icon>mdi-chevron-left</v-icon>
            </v-btn>
            <v-btn
              icon
              @click="forwardTime"
              :disabled="forbidFuture(selectedMoment)"
            >
              <v-icon>mdi-chevron-right</v-icon>
            </v-btn>
          </v-card-actions>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import TrendChart from 'vue-trend-chart';
import { format, isPast, isFuture, formatDistanceToNow, fromUnixTime, addHours, subHours } from 'date-fns';
import api from '../api';

export default {
  name: 'DataView',

  components: {
    TrendChart
  },

  data() {
    const today = new Date();
    return {
      today,
      values: [0, 0, 0, 0, 0, 0, 0],
      timeLabels: ['1hr', '50m', '40m', '30m', '20m', '10m', '0'],
      modal: false,
      latestLux: 0,
      latestMoment: null,
      selectedMoment: new Date(),
    };
  },

  mounted() {
    this.updateLatest();
    this.fetchHistory(this.selectedMoment);
  },

  methods: {
    allowPast(moment) {
      return isPast(moment);
    },

    forbidFuture(moment) {
      return isFuture(addHours(moment, 1));
    },

    backwardTime() {
      this.selectedMoment = subHours(this.selectedMoment, 1);
    },

    forwardTime() {
      this.selectedMoment = addHours(this.selectedMoment, 1);
    },

    updateLatest() {
      api.getLatestIlluminance()
        .then(data => {
          this.latestLux = data.lux;
          this.latestMoment = fromUnixTime(data.timestamp);
          this.selectedMoment = fromUnixTime(data.timestamp);
        });
    },

    fetchHistory(moment) {
      // api.getLightHistory(subHours(moment, 1), moment, 300)
      api.getLightHistory(subHours(moment, 1), moment, 300)
        .then(data => {
          if (data.length > 1) {
            // this.values = data.map(record => record.lux);
            this.values = data.map(record => record / 1024 * 100);
          } else {
            this.values = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
          }
        });
    },

    dateDisplay(date) {
      return format(date, 'yyyy-MM-dd HH:mm');
    }
  },

  computed: {
    ago() {
      return this.latestMoment == null ? '...' : formatDistanceToNow(this.latestMoment);
    },
  },

  watch: {
    selectedMoment(newMoment) {
      this.fetchHistory(newMoment);
    },
  },
};
</script>

<style lang="scss">
#history-chart {
  height: 196px;
}

.brightness-curve {
  .stroke {
    stroke: #b388ff;
    ;
    stroke-width: 2;
  }
  .fill {
    fill: #b388ff;
    opacity: 0.25;
  }
  .point {
    fill: #b388ff;
    stroke: #673ab7;
  }
}
</style>
