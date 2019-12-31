<template>
  <v-container class="px-0">
    <v-list
      subheader
      two-line
      flat
    >
      <v-subheader>Working mode</v-subheader>
      <v-list-item-group>
        <v-list-item
          v-model="mode.auto"
          @click="changeMode"
        >
          <template v-slot="{ active }">
            <v-list-item-content>
              <v-list-item-title>Auto-control</v-list-item-title>
              <v-list-item-subtitle>Current mode: {{ active ? "automatic" : "manual" }}</v-list-item-subtitle>
            </v-list-item-content>
            <v-list-item-action>
              <v-switch
                v-model="active"
                color="primary"
                :loading="mode.loading"
              />
            </v-list-item-action>
          </template>
        </v-list-item>
      </v-list-item-group>
    </v-list>

    <v-divider />

    <v-list
      subheader
      :disabled="mode.auto"
      flat
    >
      <v-subheader>Manual light control</v-subheader>
      <v-list-item-group>
        <v-list-item
          v-for="color in ['r', 'g', 'b']"
          :key="color"
          :disabled="mode.auto || mode.loading"
          :ripple="false"
        >
          <v-slider
            v-model="rgb[color]"
            prepend-icon="mdi-lightbulb"
            :label="color.toUpperCase()"
            @change="updateRGB(color, $event)"
          />
        </v-list-item>
      </v-list-item-group>
    </v-list>
  </v-container>
</template>

<script>
import api from '../api';

export default {
  name: 'ControlView',

  data: () => ({
    mode: {
      auto: false,
      loading: false,
    },
    rgb: {
      r: 0,
      g: 0,
      b: 0,
    },
  }),

  mounted() {
    this.getMode();
    this.getRGB();
  },

  methods: {
    changeMode() {
      const oldMode = this.mode.auto;
      this.mode.loading = true;
      setTimeout(() => {
        api.changeWorkingMode(this.mode.auto ? 'auto' : 'manual')
          .then(resp => {
            if (resp.status != 200) throw "failed";
          })
          .catch(() => {
            this.mode.auto = oldMode;
          })
          .finally(() => {
            this.mode.loading = false;
          });
      }, 0);
    },

    getMode() {
      this.mode.loading = true;
      api.getWorkingMode().then(resp => {
        if (resp.status != 200) throw "failed";
        this.mode.auto = resp.data.mode === "auto";
      })
      .finally(() => {
        this.mode.loading = false;
      });
    },

    updateRGB(color, value) {
      const oldValue = this.rgb[color];
      const transform = v => Math.round(v / 100.0 * 1024);
      let newValues = {
        r: transform(this.rgb.r),
        g: transform(this.rgb.g),
        b: transform(this.rgb.b),
      };
      newValues[color] = transform(value);
      api.updateRGB(newValues)
        .then(resp => {
          if (!resp.data.ok) throw "failed";
        })
        .catch(() => {
          this.rgb[color] = oldValue;
        });
    },

    getRGB() {
      api.getRGB()
        .then(data => {
          this.rgb.r = data.r / 1024.0 * 100;
          this.rgb.g = data.g / 1024.0 * 100;
          this.rgb.b = data.b / 1024.0 * 100;
        });
    },
  }
};
</script>
