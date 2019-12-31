<template>
  <v-app>
    <v-app-bar
      app
      color="primary"
      dark
    >
      <v-app-bar-nav-icon>
        <v-icon>mdi-coach-lamp</v-icon>
      </v-app-bar-nav-icon>
      <v-toolbar-title>iStreet</v-toolbar-title>

      <v-spacer />

      <template v-slot:extension>
        <v-tabs
          v-model="tab"
          fixed-tabs
          slider-color=""
          background-color="transparent"
        >
          <v-tab href="#data">
            Data
          </v-tab>
          <v-tab href="#control">
            Control
          </v-tab>
        </v-tabs>
      </template>
    </v-app-bar>

    <v-content>
      <v-tabs-items v-model="tab">
        <v-tab-item value="data">
          <data-view />
        </v-tab-item>
        <v-tab-item value="control">
          <control-view />
        </v-tab-item>
      </v-tabs-items>
    </v-content>
  </v-app>
</template>

<script>
import ControlView from './components/ControlView';
import DataView from './components/DataView';

export default {
  name: 'App',

  components: {
    ControlView,
    DataView,
  },

  data: () => ({
    tab: 'data',
  }),
};
</script>
